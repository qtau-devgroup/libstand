/* Synthesis.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef SYNTHESIS_SYNTHESIS_H
#define SYNTHESIS_SYNTHESIS_H

#include "dsp/Signal.h"

namespace stand
{

/**
 * @brief The Synthesizer class is an interface for a vocal synthesis.
 * @tpram T is a data such as score. The class that implemented Synthesizer should synthesize a signal from T.
 * @author Hal@shurabaP
 */
template<class T> class Synthesis
{
public:
    explicit Synthesis(int samplingFrequency) :
        samplingFrequency(samplingFrequency){ }
    virtual ~Synthesis(){ }

    /**
     * @brief synthesize synthesizes a signal from data.
     * @param data to synthesize.
     * @return a signal.
     */
    virtual Signal synthesize(const QSharedPointer<T> &data) = 0;

    int samplingFrequency;
};

}

#endif // SYNTHESIS_SYNTHESIS_H
