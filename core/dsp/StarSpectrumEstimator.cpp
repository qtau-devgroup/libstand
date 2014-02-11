/* StarSpectrumEstimator.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <qmath.h>
#include <QtAlgorithms>

#include "Signal.h"
#include "helpers/DoDelete.h"

#include "StarSpectrumEstimator.h"

using namespace stand;

const double StarSpectrumEstimator::F0Floor = 71.0;
const double StarSpectrumEstimator::F0Default = 150.0;


StarSpectrumEstimator::StarSpectrumEstimator(int fftLength, double f0Floor, double f0Default) :
    real(fftLength, Fft::Real), f0Floor(f0Floor), f0Default(f0Default)
{
}

int StarSpectrumEstimator::fftLength() const
{
    return real.fftLength;
}

QSharedPointer<double> StarSpectrumEstimator::estimate(const Signal &signal, float ms, float f0)
{
    double *dst = new double[fftLength()];
    // modified 0 Hz to suitable dummy f0.
    f0 = f0 < f0Floor ? f0Default : f0;
    // calculate power spectrum and set it to `dst`.
    estimatePowerSpectrum(dst, signal, ms, f0);
    // smoothe power spectrum.
    smootheSpectrum(dst, f0, real.fftLength, signal.samplingFrequency());

    return QSharedPointer<double>(dst, helper::DoDelete<double>);
}

void StarSpectrumEstimator::estimatePowerSpectrum(double *dst, const Signal &signal, float ms, float f0)
{
    int fs = signal.samplingFrequency();
    int fftLength = real.fftLength;
    int halfWindowLength = qRound(3.0 * fs / f0 / 2.0);
    double samplesAt = ms * fs / 1000.0 + 1;
    double windowSum = 0.0;
    int length = signal.size();
    for(int i = 0; i <= halfWindowLength * 2; i++)
    {
        int index = qMax(1, qMin(length, qRound(samplesAt + i - halfWindowLength))) - 1;
        double position = (double)(i - halfWindowLength) / fs / (3.0 / 2.0) + (samplesAt - qRound(samplesAt)) / fs;
        double w = 0.5 * cos(M_PI * position * f0) + 0.5;
        windowSum += w * w;
        dst[i] = signal[index] * w;
    }
    double windowAverage = sqrt(windowSum);
    for(int i = 0; i <= halfWindowLength * 2; i++)
    {
        dst[i] /= windowAverage;
    }
    for(int i = halfWindowLength * 2 + 1; i < fftLength; i++)
    {
        dst[i] = 0.0;
    }
    real.execute(Fft::Forward, dst);
    dst[fftLength / 2] = dst[1] * dst[1];
    for(int i = 1; i < fftLength / 2; i++)
    {
        dst[i] = dst[i*2] * dst[i*2] + dst[i*2+1] * dst[i*2+1];
    }
    dst[0] = dst[1];
}

void StarSpectrumEstimator::smootheSpectrum(double *dst, float f0, int fftLength, int fs)
{
    int boundary = (f0 / ((double)fs / fftLength)) + 1;
    double *mirror = new double[fftLength / 2 + boundary * 2 + 1];
    for(int i = 0; i < boundary; i++)
    {
        mirror[i] = dst[boundary - i];
    }
    for (int i = boundary; i < fftLength / 2 + boundary; i++)
    {
      mirror[i] = dst[i - boundary];
    }
    for (int i = fftLength / 2 + boundary; i < fftLength / 2 + boundary * 2 + 1; i++)
    {
      mirror[i] = dst[fftLength / 2 - (i - (fftLength / 2 + boundary)) - 1];
    }
    mirror[0] = log(mirror[0]) * fs / fftLength;
    for (int i = 1; i < fftLength / 2 + boundary * 2 + 1; i++)
    {
        mirror[i] = log(mirror[i]) * fs / fftLength + mirror[i - 1];
    }

    double mirroringOffset = -((double)boundary - 0.5) * fs / fftLength;
    double shift = (double)fs / fftLength;
    for(int i = 0; i <= fftLength / 2; i++)
    {
        double lowFrequency = (double)i / fftLength * fs - f0 / 2.0;
        int lowIndex = (lowFrequency - mirroringOffset) / shift;
        double lowDelta = mirror[lowIndex + 1] - mirror[lowIndex];
        double lowLevel = mirror[lowIndex] + lowDelta * ((lowFrequency - mirroringOffset) / shift - lowIndex);
        double highFrequency = f0 + (double)i / fftLength * fs - f0 / 2.0;
        int highIndex = (highFrequency - mirroringOffset) / shift;
        double highDelta = mirror[highIndex + 1] - mirror[highIndex];
        double highLevel = mirror[highIndex] + highDelta * ((highFrequency - mirroringOffset) / shift - highIndex);
        dst[i] = exp((highLevel - lowLevel) / f0);
    }
    delete[] mirror;
}

int StarSpectrumEstimator::fftLengthFor(int samplingFrequency, double f0Floor)
{
    return pow(2.0, 1.0 + (int)(log(3.0 * samplingFrequency / f0Floor + 1) / M_LN2));
}
