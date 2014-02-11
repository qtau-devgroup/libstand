/* MinimumPhase.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <cmath>
#include <float.h>
#include <stdio.h>

#include "MinimumPhase.h"

using namespace stand;

namespace
{
template <typename T>
void doDelete(T buf[])
{
    delete[] buf;
}
}

typedef double fftComplex[2];

MinimumPhase::MinimumPhase(int fftLength) :
    real(fftLength, Fft::Real), complex(fftLength, Fft::Complex)
{
}

QSharedPointer<double> MinimumPhase::execute(const QSharedPointer<double> powerSpectrum)
{
    int fftLength = this->fftLength();
    double *minimumPhase = new double[fftLength * 2];
    for(int i = 0; i <= fftLength / 2; i++)
    {
        minimumPhase[i] = log(powerSpectrum.data()[i] + DBL_MIN) / 2.0; // Safe guard for log(0)
    }
    // Needs mirroring, because power spectrum has information only in its front half.
    for(int i = fftLength / 2 + 1; i < fftLength; i++)
    {
        minimumPhase[i] = minimumPhase[fftLength - i];
    }
    // power spectrum -> cepstrum
    real.execute(Fft::Forward, minimumPhase);
    // Real to complex fft returns value@index[fftLength] in minimumPhase[1]
    // because imaginary parts at index[0] and index[fftLength] is always zero.
    minimumPhase[fftLength] = minimumPhase[1];
    minimumPhase[fftLength + 1] = 0.0;
    minimumPhase[1] = 0.0;

    // Calculates minimum phase spectrum below.
    for(int i = 2; i < fftLength; i += 2)
    {
        minimumPhase[i] *= 2.0;
        minimumPhase[i + 1] *= -2.0;
    }
    for(int i = fftLength + 2; i < fftLength * 2; i++)
    {
        minimumPhase[i] = 0.0;
    }
    complex.execute(Fft::Forward, minimumPhase);
    double re, im;
    for(int i = 0; i <= fftLength; i += 2)
    {
        // Needs scaling with FFT length.
        re = exp(minimumPhase[i] / fftLength);
        im = minimumPhase[i + 1] / fftLength;
        minimumPhase[i] = re * cos(im);
        minimumPhase[i + 1] = re * sin(im);
    }
    minimumPhase[1] = minimumPhase[fftLength];
    return QSharedPointer<double>(minimumPhase, doDelete<double>);
}
