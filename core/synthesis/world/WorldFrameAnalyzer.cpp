/* WorldFrameAnalyzer.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "util/MusicalNote.h"

#include "WorldFrameAnalyzer.h"

using namespace stand;

QSharedPointer<WorldFrame> WorldFrameAnalyzer::analyze(const PhonemeKey &key,
    const WaveformFrameInfoList &infos,
    const QList<QSharedPointer<WorldWaveform> > &waveforms)
{
    int fftLength = 0; // use biggest FFT size.
    int samplingFrequency = 0; // use biggest sampling frequency.
    foreach(const auto &waveform, waveforms)
    {
        int length = StarSpectrumEstimator::fftLengthFor(waveform->signal.samplingFrequency());
        fftLength = qMax(fftLength, length);
        samplingFrequency = qMax(samplingFrequency, waveform->signal.samplingFrequency());
    }

    WorldFrame *result = new WorldFrame(fftLength, samplingFrequency, MusicalNote::frequencyFromNote(key.noteNumber));
    result->clear();

    for(int i = 0; i < infos.size() && i < waveforms.size(); i++)
    {
        const WaveformFrameInfo &piece = infos[i];
        const auto &waveform = waveforms[i];
        if(waveform.isNull())
        {
            continue;
        }
        int srcSamplingFrequency = waveform->signal.samplingFrequency();
        int srcFftLength = fftLengthFor(srcSamplingFrequency);
        double msPosition = piece.msPosition;
        double f0 = waveform->f0Contour.at(msPosition);
        auto spectrum = star(srcFftLength)->estimate(waveform->signal, msPosition, f0);
        auto residual = platinum(srcFftLength)->calculate(waveform->signal, waveform->peakIndices.at(msPosition), f0, spectrum);

        double srcEndIndex = qMin((double)samplingFrequency / srcSamplingFrequency * srcFftLength, (double)srcFftLength);
        int dstEndIndex = qMin(result->fftLength, (int)(srcEndIndex * srcSamplingFrequency / samplingFrequency)) / 2;
        for(int dstIndex = 0; dstIndex < dstEndIndex; dstIndex++)
        {
            double frequency = (double)samplingFrequency / result->fftLength * dstIndex;
            int srcIndex = frequency / waveform->signal.samplingFrequency() * srcFftLength;
            result->spectrum.data()[dstIndex] *= pow(spectrum.data()[srcIndex], piece.amplify);
            result->residual.data()[dstIndex * 2] += residual.data()[srcIndex * 2] * piece.amplify;
            result->residual.data()[dstIndex * 2 + 1] += residual.data()[srcIndex * 2 + 1] * piece.amplify;
        }
        double frequency = (double)samplingFrequency / result->fftLength * dstEndIndex;
        int srcIndex = frequency / waveform->signal.samplingFrequency() * srcFftLength;
        result->spectrum.data()[dstEndIndex] *= pow(spectrum.data()[srcIndex], piece.amplify);
    }

    return QSharedPointer<WorldFrame>(result);
}

QSharedPointer<StarSpectrumEstimator> WorldFrameAnalyzer::star(int fftLength)
{
    return QSharedPointer<StarSpectrumEstimator>(new StarSpectrumEstimator(fftLength));
}

QSharedPointer<PlatinumResidualCalculator> WorldFrameAnalyzer::platinum(int fftLength)
{
    return QSharedPointer<PlatinumResidualCalculator>(new PlatinumResidualCalculator(fftLength));
}

int WorldFrameAnalyzer::fftLengthFor(int samplingFrequency)
{
    return StarSpectrumEstimator::fftLengthFor(samplingFrequency);
}
