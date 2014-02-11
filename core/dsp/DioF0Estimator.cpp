/* DioF0Estimator.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <qmath.h>
#include <QtAlgorithms>
#include <float.h>
#include "dsp/Decimator.h"
#include "dsp/FftSg.h"
#include "dsp/Signal.h"
#include "dsp/WindowFunctions.h"
#include "dsp/DioF0Estimator.h"

#include "helpers/DioHelper.h"

using namespace stand;

const static double Log2 = log(2.0);
const double DioF0Estimator::DefaultF0Floor = 80.0;
const double DioF0Estimator::DefaultF0Ceil = 640.0;
const double DioF0Estimator::DefaultChannelsInOctave = 2.0;
const double DioF0Estimator::DefaultDecimatedFs = 4000.0;

DioF0Estimator::DioF0Estimator(double f0Floor, double f0Ceil, double channelsInOctave, double decimatedFs)
{
    floorF0 = f0Floor;
    ceilF0 = f0Ceil;
    channelsInOctave = channelsInOctave;
    bandsCount = 2 + (log(ceilF0 / floorF0) / Log2 * channelsInOctave);
    decimatedFs = decimatedFs;
}

DioF0Estimator::Spectrum DioF0Estimator::createDecimatedSpectrum(const Signal &signal, int decimationRatio)
{
    int decimatedLength = 1 + signal.size() / decimationRatio;
    int fftLength = fft->fftLength;
    double *decimatedWave = new double[fftLength];
    Decimator::decimate(signal, decimationRatio, decimatedWave, decimatedLength);
    double mean = 0.0;
    for(int i = 0; i < decimatedLength; i++)
    {
        mean += decimatedWave[i];
    }
    mean /= decimatedLength;
    for(int i = 0; i < decimatedLength; i++)
    {
        decimatedWave[i] -= mean;
    }
    for(int i = decimatedLength; i < fftLength; i++)
    {
        decimatedWave[i] = 0.0;
    }
    fft->execute(Fft::Forward, decimatedWave);
    return Spectrum(decimatedWave, decimatedLength, fftLength, (double)signal.samplingFrequency() / decimationRatio);
}

void DioF0Estimator::getFilteredSignal(double *dst, int halfAverageLength, const Spectrum &spectrum)
{
    // First, `dst` contains waveform of Nuttall window corresponding to halfAverageLength.
    for (int i = halfAverageLength * 2; i < spectrum.size; i++)
    {
        dst[i] = 0.0;
    }
    WindowFunctions::nuttall(dst, halfAverageLength * 4);
    // Then, `dst` becomes spectrum of that Nuttal window.
    fft->execute(Fft::Forward, dst);

    // Third, `dst` will be a convolution of the decimated spectrum and nuttal window spectrum.
    dst[0] *= spectrum.data[0];
    dst[1] *= spectrum.data[1];
    for (int i = 1; i <= spectrum.size / 2; ++i) {
        double tmp = spectrum.data[i * 2] * dst[i * 2 + 1] + spectrum.data[i * 2 + 1] * dst[i * 2];
        dst[i * 2] = spectrum.data[i * 2] * dst[i * 2] - spectrum.data[i * 2 + 1] * dst[i * 2 + 1];
        dst[i * 2 + 1] = tmp;
    }
    // Last, `dst` gets a waveform.
    fft->execute(Fft::Inverse, dst);

    // And compensate the delay of the signal.
    int offset = halfAverageLength * 2;
    int end = qMin(spectrum.length, spectrum.size - offset);
    for (int i = 0; i < end; i++)
    {
        dst[i] = dst[i + offset];
    }
}

Contour<float> DioF0Estimator::estimate(const Spectrum &spectrum, int length, int fs, double msFramePeriod)
{
    int f0Length = length / (double)fs / msFramePeriod * 1000.0 + 1;
    double **candidates = newMatrix(f0Length, bandsCount);
    double **stabilities = newMatrix(f0Length, bandsCount);

    double *filteredSignal = new double[spectrum.size];
    for (int i = 0; i < bandsCount; i++)
    {
        double boundaryF0 = floorF0 * pow(2.0, i / channelsInOctave);
        getFilteredSignal(filteredSignal, qRound(spectrum.fs / boundaryF0 / 2.0), spectrum);

        getCandidates(candidates[i], stabilities[i], f0Length, msFramePeriod, boundaryF0, ceilF0, floorF0, filteredSignal, spectrum.length, spectrum.fs);
    }
    Contour<float> result(getF0Contour(candidates, stabilities, bandsCount, f0Length, msFramePeriod), msFramePeriod);
    delete[] filteredSignal;
    deleteMatrix(stabilities);
    deleteMatrix(candidates);
    return result;
}

Contour<float> DioF0Estimator::estimate(const Signal &signal, double msFramePeriod)
{
    int decimationRatio = qMax(1, qMin(12, (int)(signal.samplingFrequency() / decimatedFs)));
    int decimatedLength = 1 + signal.size() / decimationRatio;
    fft = new Fft(Fft::suitableLength(decimatedLength), Fft::Real);

    Spectrum decimatedSpectrum(createDecimatedSpectrum(signal, decimationRatio));

    Contour<float> result(estimate(decimatedSpectrum, signal.size(), signal.samplingFrequency(), msFramePeriod));

    delete fft;

    return result;
}

