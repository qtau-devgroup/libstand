/* WorldFrameSynthesizerTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMESYNTHESIZERTEST_H
#define WORLDFRAMESYNTHESIZERTEST_H

#include <QTest>

#include "dsp/Signal.h"
#include "dsp/world/world_synthesis.h"
#include "synthesis/world/WorldFrameSynthesizer.h"

#include "AutoTest.h"

namespace stand
{

class WorldFrameSynthesizerTest : public QObject
{
    Q_OBJECT
private slots:
    void synthesize_properly_synthesize_the_same_waveform_that_world_synthesize()
    {
        int samplingFrequency = 44100;
        double f0 = 0;
        auto frame = QSharedPointer<WorldFrame>(new WorldFrame(2048, samplingFrequency, f0));
        Signal signal(samplingFrequency, samplingFrequency);
        double *spectrum = new double[2048];
        double *residual = new double[2048];
        for(int i = 0; i < 2048; i++)
        {
            spectrum[i] = frame->spectrum.data()[i] = frame->residual.data()[i] = 2048 - i;
        }

        // WORLD's residual spectrum is a bit different from FFTSG :P
        residual[0] = frame->residual.data()[0];
        for(int i = 1; i < 1024; i++)
        {
            residual[i * 2 - 1] = frame->residual.data()[i * 2];
            residual[i * 2] = frame->residual.data()[i * 2 + 1];
        }
        residual[2047] = frame->residual.data()[1];
        double *expected = new double[samplingFrequency];

        for(int i = 0; i < signal.size(); i++)
        {
            expected[i] = signal[i] = 0.0f;
        }

        Synthesize(&f0, 1, &spectrum, &residual, 2048, 1.0, samplingFrequency, samplingFrequency, expected);
        WorldFrameSynthesizer(samplingFrequency).synthesize(signal, frame, 0);

        for(int i = 0; i < signal.size(); i++)
        {
            QCOMPARE(signal[i], (float)expected[i]);
        }
    }

    void synthesize_properly_synthesize_white_spectrum_the_same_waveform_that_world_synthesize()
    {
        int samplingFrequency = 44100;
        double f0 = 0;
        auto frame = QSharedPointer<WorldFrame>(new WorldFrame(2048, samplingFrequency, f0));
        Signal signal(samplingFrequency, samplingFrequency);
        double *spectrum = new double[2048];
        double *residual = new double[2048];
        for(int i = 0; i < 2048; i++)
        {
            spectrum[i] = 1.0;
            frame->spectrum.data()[i] = 1.0;
            frame->residual.data()[i] = (i % 2 == 0) ? 1.0 : 0.0;
        }
        frame->residual.data()[1] = 1.0;

        // WORLD's residual spectrum is a bit different from FFTSG :P
        residual[0] = frame->residual.data()[0];
        for(int i = 1; i < 1024; i++)
        {
            residual[i * 2 - 1] = frame->residual.data()[i * 2];
            residual[i * 2] = frame->residual.data()[i * 2 + 1];
        }
        residual[2047] = frame->residual.data()[1];
        double *expected = new double[samplingFrequency];

        for(int i = 0; i < signal.size(); i++)
        {
            expected[i] = signal[i] = 0.0f;
        }

        Synthesize(&f0, 1, &spectrum, &residual, 2048, 1.0, samplingFrequency, samplingFrequency, expected);
        WorldFrameSynthesizer(samplingFrequency).synthesize(signal, frame, 0);

        for(int i = 0; i < signal.size(); i++)
        {
            QCOMPARE(signal[i], (float)expected[i]);
        }
    }
};

}

DECLARE_TEST(stand::WorldFrameSynthesizerTest)

#endif // WORLDFRAMESYNTHESIZERTEST_H
