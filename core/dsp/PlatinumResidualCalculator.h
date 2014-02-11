/* PlatinumResidualCalculator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef PLATINUMSPECTRUMESTIMATOR_H
#define PLATINUMSPECTRUMESTIMATOR_H

#include <QList>

#include "dsp/FftSg.h"
#include "dsp/MinimumPhase.h"

namespace stand
{

class Signal;

/**
 * @brief The PlatinumResidualCalculator class calculates a residual spectrum of WORLD.
 *        The residual is calculated from one frame spectrum by inverted filter of power spectrum envelope.
 * @see   http://www.slp.is.ritsumei.ac.jp/~morise/world/
 * @author Hal@shurabaP
 */
class PlatinumResidualCalculator
{
public:
    /**
     * @brief PlatinumResidualCalculator is a default constructor.
     * @param fftLength is a FFT size.
     */
    explicit PlatinumResidualCalculator(int fftLength);
    virtual ~PlatinumResidualCalculator(){ }

    /**
     * @brief calculate calculates PLATINUM residual spectrum to `dst`.
     * @param signal is a vocal wave.
     * @param peakIndex is the index of signal peak. Peak picked index.
     * @param f0 is a instant frequency at peakIndex.
     * @param power is a instant power spectrum at peakIndex.
     */
    virtual QSharedPointer<double> calculate(const Signal &signal, int peakIndex, float f0, const QSharedPointer<double> power);

private:
    int fftLength;

    Fft real;
    MinimumPhase minimumPhase;
};

}

#endif // PLATINUMSPECTRUMESTIMATOR_H
