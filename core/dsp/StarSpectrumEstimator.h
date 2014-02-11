/* StarSpectrumEstimator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef STARSPECTRUMESTIMATOR_H
#define STARSPECTRUMESTIMATOR_H

#include <QSharedPointer>

#include "dsp/FftSg.h"
#include "dsp/SynchronousSpectrumEstimator.h"

namespace stand
{

class Signal;

/**
 * @brief The StarSpectrumEstimator class is an implementaion of SynchronousSpectrumEstimator.
 *        STAR is an estimation method of power spectrum. It smoothes power spectrum.
 * @see   http://www.slp.is.ritsumei.ac.jp/~morise/world/
 * @author Hal@shurabaP
 */
class StarSpectrumEstimator : public SynchronousSpectrumEstimator
{
public:
    static const double F0Floor;
    static const double F0Default;
public:
    virtual ~StarSpectrumEstimator(){ }

    /**
     * @brief StarSpectrumEstimator is a default constructor.
     * @param fftLength is a FFT size.
     * @param f0Floor
     * @param f0Default
     */
    StarSpectrumEstimator(int fftLength, double f0Floor = F0Floor, double f0Default = F0Default);

    /**
     * @brief estimate esitamtes power spectrum by STAR.
     * @param signal is a signal to analyze.
     * @param ms is a time position to analyze.
     * @param f0 is a instant frequency at `ms`[msec].
     * @return STAR power spectrum.
     */
    virtual QSharedPointer<double> estimate(const Signal &signal, float ms, float f0);

    /**
     * @brief fftLength represents neccessary length for the destination buffer.
     * @return
     */
    int fftLength() const;

    /**
     * @brief fftLengthFor returns FFT size for sampling frequency.
     */
    static int fftLengthFor(int samplingFrequency, double f0Floor = F0Floor);
private:
    void estimatePowerSpectrum(double *dst, const Signal &signal, float ms, float f0);
    void smootheSpectrum(double *dst, float f0, int fftLength, int fs);
    Fft real;
    double f0Floor;
    double f0Default;
};
}

#endif // STARSPECTRUMESTIMATOR_H
