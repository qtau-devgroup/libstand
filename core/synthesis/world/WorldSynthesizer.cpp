/* WorldSynthesizer.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "synthesis/FrameRenderer.h"
#include "WorldFrameSynthesizer.h"

#include "WorldSynthesizer.h"

using namespace stand;

Signal WorldSynthesizer::synthesize(const QSharedPointer<FrameProvider<WorldFrame> > &data)
{
    return renderer->render(data, synthesizer);
}

QSharedPointer<WorldSynthesizer> DefaultWorldSynthesizerFactory::apply(int samplingFrequency) const
{
    QSharedPointer<FrameSynthesizer<WorldFrame> > synthesizer = QSharedPointer<FrameSynthesizer<WorldFrame> >(new WorldFrameSynthesizer(samplingFrequency));
    QSharedPointer<FrameRenderer<WorldFrame> > renderer = QSharedPointer<FrameRenderer<WorldFrame> >(new SimpleRenderer<WorldFrame>());
    WorldSynthesizer *result = new WorldSynthesizer(synthesizer, renderer, samplingFrequency);
    return QSharedPointer<WorldSynthesizer>(result);
}
