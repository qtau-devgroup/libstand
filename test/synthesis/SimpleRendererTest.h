/* SimpleRendererTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef SIMPLERENDERERTEST_H
#define SIMPLERENDERERTEST_H

#include <QTest>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "synthesis/FrameRenderer.h"
#include "synthesis/FrameSynthesizer.h"

#include "AutoTest.h"

using namespace ::testing;

namespace stand
{

class MockProvider : public FrameProvider<double>
{
public:
    MOCK_CONST_METHOD1_T(at, const QSharedPointer<double>(double ms));
    MOCK_CONST_METHOD0(msLength, double());
};

class MockSynthesizer : public FrameSynthesizer<double>
{
public:
    explicit MockSynthesizer(int samplingFrequency): FrameSynthesizer<double>(samplingFrequency){ }
    MOCK_METHOD3_T(synthesize, double(Signal &dst, const QSharedPointer<double> &src, double ms));
};

class SimpleRendererTest : public QObject
{
    Q_OBJECT
private slots:
    void render_should_locate_siganl()
    {
        double msLength = 1000;
        double value = 1.0;
        double f0 = 16;
        int samplingFrequency = 256;
        MockProvider *providerInternal = new MockProvider;
        MockSynthesizer *synthesizerInternal = new MockSynthesizer(samplingFrequency);
        QSharedPointer<FrameProvider<double> > provider = QSharedPointer<FrameProvider<double> >(providerInternal);
        QSharedPointer<FrameSynthesizer<double> > synthesizer = QSharedPointer<FrameSynthesizer<double> >(synthesizerInternal);
        QSharedPointer<double> atResult = QSharedPointer<double>(new double(value));

        EXPECT_CALL(*providerInternal, msLength())
            .Times(1)
            .WillOnce(Return(msLength));
        EXPECT_CALL(*providerInternal, at(_))
            .Times((int)(samplingFrequency / f0))
            .WillRepeatedly(Return(atResult));
        EXPECT_CALL(*synthesizerInternal, synthesize(_, atResult, _))
            .Times((int)(samplingFrequency / f0))
            .WillRepeatedly(Return(f0));

        Signal result = SimpleRenderer<double>().render(provider, synthesizer);

        QCOMPARE(result.samplingFrequency(), samplingFrequency);
        QCOMPARE(result.size(), samplingFrequency);
    }

    void render_should_empty_signal_if_both_provider_and_synthesizer_is_null()
    {
        MockProvider *providerInternal = new MockProvider;
        MockSynthesizer *synthesizerInternal = new MockSynthesizer(0);
        QSharedPointer<FrameProvider<double> > provider = QSharedPointer<FrameProvider<double> >(providerInternal);
        QSharedPointer<FrameSynthesizer<double> > synthesizer = QSharedPointer<FrameSynthesizer<double> >(synthesizerInternal);
        QSharedPointer<FrameProvider<double> > providerNull = QSharedPointer<FrameProvider<double> >();
        QSharedPointer<FrameSynthesizer<double> > synthesizerNull = QSharedPointer<FrameSynthesizer<double> >();

        Signal result;
        result = SimpleRenderer<double>().render(provider, synthesizerNull);
        QCOMPARE(result.empty(), true);
        result = SimpleRenderer<double>().render(providerNull, synthesizer);
        QCOMPARE(result.empty(), true);
        result = SimpleRenderer<double>().render(providerNull, synthesizerNull);
        QCOMPARE(result.empty(), true);
    }
};

}

DECLARE_TEST(stand::SimpleRendererTest)

#endif // SIMPLERENDERERTEST_H
