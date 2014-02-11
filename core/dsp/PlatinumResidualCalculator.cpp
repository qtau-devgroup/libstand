/* PlatinumResidualCalculator.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <float.h>
#include <qmath.h>
#include "Signal.h"

#include "helpers/DoDelete.h"

#include "PlatinumResidualCalculator.h"

using namespace stand;

PlatinumResidualCalculator::PlatinumResidualCalculator(int fftLength) :
    real(fftLength, Fft::Real), minimumPhase(fftLength)
{
    this->fftLength = fftLength;
}

QSharedPointer<double> PlatinumResidualCalculator::calculate(const Signal &signal, int peakIndex, float f0, const QSharedPointer<double> power)
{
    double *dst = new double[fftLength];
    double T0 = signal.samplingFrequency() / f0;
    int windowLength = qRound(2.0 * T0);
    for(int i = 0; i < windowLength; i++)
    {
        double w = 0.5 - 0.5 * cos(2.0 * M_PI * (i + 1.0) / (windowLength + 1.0));
        dst[i] = signal[qMin(signal.size() - 1, qMax(0, i + peakIndex - qRound(T0)))] * w;
    }
    for(int i = windowLength; i < fftLength; i++)
    {
        dst[i] = 0.0;
    }
    real.execute(Fft::Forward, dst);
    QSharedPointer<double> workingBuffer = minimumPhase.execute(power);
    const double *working = workingBuffer.data();
    dst[0] = dst[0] / (working[0] + DBL_MIN);
    dst[1] = dst[1] / (working[1] + DBL_MIN);
    for(int i = 1; i < fftLength / 2; i++)
    {
        double r = working[i * 2] * working[i * 2] + working[i * 2 + 1] * working[i * 2 + 1] + DBL_MIN;
        double re = (working[i * 2] * dst[i * 2] + working[i * 2 + 1] * dst[i * 2 + 1]) / r;
        double im = (working[i * 2] * dst[i * 2 + 1] - working[i * 2 + 1] * dst[i * 2]) / r;
        dst[i * 2] = re;
        dst[i * 2 + 1] = im;
    }
    return QSharedPointer<double>(dst, helper::DoDelete<double>);
}
