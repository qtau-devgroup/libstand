/* SynchronousSpectrumEstimator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef SYNCHRONOUSSPECTRUMESTIMATOR_H
#define SYNCHRONOUSSPECTRUMESTIMATOR_H

#include <QSharedPointer>

namespace stand
{

class Signal;

/**
 * @brief The SynchronousSpectrumEstimator class is an interface class of pitch synchronous spectrum estimation.
 */
class SynchronousSpectrumEstimator
{
public:
    /**
     * @brief estimate should estimate power spectrum to the destination buffer `dst`.
     *        SynchronousSpectrumEstimator should return the neccessary length for destination buffer by fftLength.
     * @param signal is a signal to analyze.
     * @param ms is milli seconds to analyze at.
     * @param f0 is instant frequency at ms[msec].
     * @return spectrum.
     */
    virtual QSharedPointer<double> estimate(const Signal &signal, float ms, float f0) = 0;

    /**
     * @brief fftLength reprensets neccessary buffer length for the `estimate` method.
     * @return
     */
    virtual int fftLength() const = 0;
};

}

#endif // SYNCHRONOUSSPECTRUMESTIMATOR_H
