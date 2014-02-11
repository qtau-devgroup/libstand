/* MinimumPhase.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef MINIMUMPHASE_H
#define MINIMUMPHASE_H

#include <QSharedPointer>

#include "dsp/FftSg.h"

namespace stand
{

/**
 * @brief The MinimumPhase class calculates minimum phase spectrum.
 * @author Hal@shurabaP
 */
class MinimumPhase
{
public:
    /**
     * @brief MinimumPhase is a default constructor.
     * @param fftLength is a FFT size.
     */
    explicit MinimumPhase(int fftLength);

    /**
     * @brief execute calculates minimum phase spectrum.
     * @param powerSpectrum is a src buffer. This buffer length must be FFT size.
     *        This function returns a spectrum formatted like FFTSG.
     *        data[1] is actually a real part at fftLength.
     * @return minimum phase spectrum.
     */
    QSharedPointer<double> execute(const QSharedPointer<double> powerSpectrum);

    int fftLength() const
    {
        return real.fftLength;
    }

private:
    Fft real;
    Fft complex;
};

}

#endif // MINIMUMPHASE_H
