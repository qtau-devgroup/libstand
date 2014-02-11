/* WorldSynthesizer.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDSYNTHESIZER_H
#define WORLDSYNTHESIZER_H

#include "synthesis/FrameRenderer.h"
#include "synthesis/Synthesis.h"
#include "synthesis/world/WorldFrame.h"

namespace stand
{

/**
 * @brief The WorldSynthesizer class is a synthezier with WORLD.
 * @author Hal@shurabaP
 */
class WorldSynthesizer : public Synthesis<FrameProvider<WorldFrame> >
{
public:
    WorldSynthesizer(
        QSharedPointer<FrameSynthesizer<WorldFrame> > synthesizer,
        QSharedPointer<FrameRenderer<WorldFrame> > renderer,
        int samplingFrequency = 44100
    ) : Synthesis<FrameProvider<WorldFrame> >(samplingFrequency), synthesizer(synthesizer), renderer(renderer)
    {
    }

    virtual ~WorldSynthesizer(){ }

    /**
     * @brief synthesize waveform from the given WorldFrames.
     * @param data to synthesize signal with.
     * @return synthesized signal.
     */
    virtual Signal synthesize(const QSharedPointer<FrameProvider<WorldFrame> > &data);
private:
    QSharedPointer<FrameSynthesizer<WorldFrame> > synthesizer;
    QSharedPointer<FrameRenderer<WorldFrame> > renderer;
};

/**
 * @brief The WorldSynthesizerFactory class is a factory class of WorldSynthesizer.
 * @author Hal@shurabaP
 */
class WorldSynthesizerFactory
{
public:
    virtual ~WorldSynthesizerFactory(){ }
    /**
     * @brief apply is a factory method of WorldSynthesizer.
     * @param samplingFrequency
     * @return WorldSynthesizer.
     */
    virtual QSharedPointer<WorldSynthesizer> apply(int samplingFrequency) const = 0;
};

/**
 * @brief The DefaultWorldSynthesizerFactory class is a default synthesizer factory
 */
class DefaultWorldSynthesizerFactory : public WorldSynthesizerFactory
{
public:
    ~DefaultWorldSynthesizerFactory(){ }
    virtual QSharedPointer<WorldSynthesizer> apply(int samplingFrequency) const;
};

}

#endif // WORLDSYNTHESIZER_H
