/* FrameRenderer.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef SYNTHESIS_FRAMERENDERER_H
#define SYNTHESIS_FRAMERENDERER_H

#include <QSharedPointer>

#include "dsp/Signal.h"
#include "synthesis/FrameProvider.h"
#include "synthesis/FrameSynthesizer.h"

namespace stand
{

/**
 * @brief The FrameRenderer class represents an algorithm to locate siganal from FrameSynthesizer.
 * @tparam T is a data type.
 * @author Hal@shurabaP
 */
template <class T> class FrameRenderer
{
public:
    virtual ~FrameRenderer(){ }

    /**
     * @brief render renders a waveform from `data` with `synthesizer`
     * @param data is data to synthesize signal from.
     * @param synthesizer is an algorithm to synthesize signal.
     * @return synthesized signal.
     */
    virtual Signal render(const QSharedPointer<FrameProvider<T> > &frameProvider, QSharedPointer<FrameSynthesizer<T> > synthesizer) = 0;
};

/**
 * @brief The SimpleRenderer class is a simple renderer.
 *        SimpleRenderer renders a waveform according to f0 which synthesizer returns.
 *        If Synthesizer returns 0.0[Hz], SimpleRenderer use defaultF0 instead.
 * @tparam T is a data type. T should have a `double msLength() const` method that returns length[ms].
 * @author Hal@shurabaP
 */
template <class T> class SimpleRenderer : public FrameRenderer<T>
{
public:
    explicit SimpleRenderer(double defaultF0 = 70.0) :
        defaultF0(defaultF0){ }
    virtual ~SimpleRenderer(){ }

    /**
     * @brief render renders a waveform. SimpleRenderer uses f0 to locate each frame signal.
     * @param data is data to synthesize signal from.
     * @param synthesizer is an algorithm to synthesize signal.
     * @return synthesized signal.
     */
    virtual Signal render(const QSharedPointer<FrameProvider<T> > &frameProvider, QSharedPointer<FrameSynthesizer<T> > synthesizer)
    {
        if(frameProvider.isNull() || synthesizer.isNull())
        {
            return Signal();
        }

        double secLength = frameProvider->msLength() / 1000.0;
        int samplingFrequency = synthesizer->samplingFrequency();
        int signalLength = secLength * samplingFrequency + 0.5;

        Signal result(signalLength, samplingFrequency);
        for(int i = 0; i < result.size(); i++)
        {
            result[i] = 0.0f;
        }

        double sec = 0.0;
        for(int index = 0; index < result.size(); index = sec * samplingFrequency)
        {
            double ms = sec * 1000.0;

            const QSharedPointer<T> frame = frameProvider->at(ms);
            double f0 = synthesizer->synthesize(result, frame, ms);

            f0 = (f0 == 0.0) ? defaultF0 : f0;
            sec += 1.0 / f0;
        }

        return result;
    }

private:
    double defaultF0;
};

}

#endif // SYNTHESIS_FRAMERENDERER_H
