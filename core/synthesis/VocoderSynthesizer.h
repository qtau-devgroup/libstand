#ifndef VOCODERSYNTHESIZER_H
#define VOCODERSYNTHESIZER_H

#include <QSharedPointer>

#include "Synthesizer.h"

namespace org
{
namespace stand
{
namespace synthesis
{

template <class T> class Vocoder;
template <class T> class FrameRenderer;

/**
 * @brief The VocoderSynthesizer class is an implementation of Synthesizer class.
 *        VocoderSynthesizer reprensents a vocal synthesizer with a vocoder system.
 * @tpram T is a data such as score. The class that implemented Synthesizer should synthesize a signal from T.
 * @author Hal@shurabaP
 */
template <class T> class VocoderSynthesizer : public Synthesizer<T>
{
public:
    VocoderSynthesizer(int samplingFrequency, QSharedPointer<Vocoder *> vocoder, QSharedPointer<FrameRenderer *> renderer);
    virtual ~VocoderSynthesizer(){ }

    Signal synthesize(const T &data);
};

}
}
}

#endif // VOCODERSYNTHESIZER_H
