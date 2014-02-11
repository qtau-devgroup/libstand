/* FrameSynthesizer.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef FRAMESYNTHESIZER_H
#define FRAMESYNTHESIZER_H

#include <QSharedPointer>

namespace stand
{

class Signal;

/**
 * @brief The FrameSynthesizer represents an algorithm to synthesize one frame signal at the specified time.
 * @tparam T is a data type.
 * @author Hal@shurabaP
 */
template <class T> class FrameSynthesizer
{
public:
    explicit FrameSynthesizer(int samplingFrequency) :
        fs(samplingFrequency)
    {
    }

    virtual ~FrameSynthesizer(){ }

    /**
     * @brief synthesize synthesizes one frame.
     *        synthesize should add data to `dst`, not overwrite data.
     *        This feature is because of performance.
     * @param dst is a target to write data in.
     * @param src is data to synthesize.
     * @param ms is a milli second to synthesize.
     * @return f0.
     */
    virtual double synthesize(Signal &dst, const QSharedPointer<T> &src, double ms) = 0;

    int samplingFrequency() const
    {
        return fs;
    }
    void setSamplingFrequency(int samplingFrequency)
    {
        fs = samplingFrequency;
    }

private:
    int fs;
};

}

#endif // FRAMESYNTHESIZER_H
