/* WorldFrameAnalyzerTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMEANALYZERTEST_H
#define WORLDFRAMEANALYZERTEST_H

#include <QTest>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "synthesis/world/WorldFrameAnalyzer.h"

#include "AutoTest.h"

using namespace ::testing;

namespace stand
{

class TestWorldFrameAnalyzer : public WorldFrameAnalyzer
{
public:
    TestWorldFrameAnalyzer(QSharedPointer<StarSpectrumEstimator> mockStar, QSharedPointer<PlatinumResidualCalculator> mockPlatinum) :
        mockStar(mockStar), mockPlatinum(mockPlatinum){ }
protected:
    QSharedPointer<StarSpectrumEstimator> star(int /*fftLength*/)
    {
        return mockStar;
    }

    QSharedPointer<PlatinumResidualCalculator> platinum(int /*fftLength*/)
    {
        return mockPlatinum;
    }

private:
    QSharedPointer<StarSpectrumEstimator> mockStar;
    QSharedPointer<PlatinumResidualCalculator> mockPlatinum;
};

class MockStarSpectrumEstimator : public StarSpectrumEstimator
{
public:
    explicit MockStarSpectrumEstimator(int fftLength) : StarSpectrumEstimator(fftLength){ }
    MOCK_METHOD3_T(estimate, QSharedPointer<double>(const Signal &signal, float ms, float f0));
};

class MockPlatinumResidualCalculator : public PlatinumResidualCalculator
{
public:
    explicit MockPlatinumResidualCalculator(int fftLength) : PlatinumResidualCalculator(fftLength){ }
    MOCK_METHOD4_T(calculate, QSharedPointer<double>(const Signal &signal, int peakIndex, float f0, const QSharedPointer<double> power));
};

class WorldFrameAnalyzerTest : public QObject
{
    Q_OBJECT
private slots:
    void analyze_should_successfuly_return_WorldFrame_with_properly_mixed_by_amplify()
    {
        PhonemeKey key("pronounce", 1.0, 0, 0, 0);
        int samplingFrequency1 = 44100;
        int samplingFrequency2 = 44100;
        Contour<float> f0(1000, 1.0); Contour<int> peak(1000, 1.0);
        for(int i = 0; i < 1000; i++)
        {
            f0.append(0.0f); peak.append(0);
        }
        WorldWaveform *wave1 = new WorldWaveform(Signal(samplingFrequency1, samplingFrequency1), f0, peak, 1.0);
        WorldWaveform *wave2 = new WorldWaveform(Signal(samplingFrequency2, samplingFrequency2), f0, peak, 1.0);
        QList<QSharedPointer<WorldWaveform> > waveforms; waveforms.append(QSharedPointer<WorldWaveform>(wave1)); waveforms.append(QSharedPointer<WorldWaveform>(wave2));

        WaveformFrameInfo piece1("", 0.0, 0.7);
        WaveformFrameInfo piece2("", 0.0, 0.3);
        QList<WaveformFrameInfo> elements; elements.append(piece1); elements.append(piece2);

        int fftLength = 2048;
        MockStarSpectrumEstimator *star = new MockStarSpectrumEstimator(fftLength);
        MockPlatinumResidualCalculator *platinum = new MockPlatinumResidualCalculator(fftLength);
        auto mockStar = QSharedPointer<StarSpectrumEstimator>(star);
        auto mockPlatinum = QSharedPointer<PlatinumResidualCalculator>(platinum);

        QSharedPointer<double> spectrum1(new double[fftLength]), spectrum2(new double[fftLength]), residual1(new double[fftLength]), residual2(new double[fftLength]);
        for(int i = 0; i < fftLength; i++)
        {
            spectrum1.data()[i] = residual1.data()[i] = 1.0 * i; spectrum2.data()[i] = residual2.data()[i] = 2.0 * i;
        }

        InSequence s;
        EXPECT_CALL(*star, estimate(wave1->signal, 0, 0)).Times(1).WillOnce(Return(spectrum1));
        EXPECT_CALL(*platinum, calculate(wave1->signal, 0, 0, spectrum1)).Times(1).WillOnce(Return(residual1));
        EXPECT_CALL(*star, estimate(wave2->signal, 0, 0)).Times(1).WillOnce(Return(spectrum2));
        EXPECT_CALL(*platinum, calculate(wave2->signal, 0, 0, spectrum2)).Times(1).WillOnce(Return(residual2));

        auto result = TestWorldFrameAnalyzer(mockStar, mockPlatinum).analyze(key, elements, waveforms);
        for(int i = 0; i < fftLength; i++)
        {
            QCOMPARE(result->residual.data()[i], 1.0 * i * 0.7 + 2.0 * i * 0.3);
        }
        for(int i = 0; i < fftLength / 2; i++)
        {
            QCOMPARE(result->spectrum.data()[i], pow(1.0 * i, 0.7) * pow(2.0 * i, 0.3));
        }
    }

    void analyze_should_successfuly_return_WorldFrame_with_properly_stretched_by_sampling_frequency()
    {
        PhonemeKey key("pronounce", 1.0, 0, 0, 0);
        int samplingFrequency1 = 44100;
        int samplingFrequency2 = 40000;
        Contour<float> f0(1000, 1.0); Contour<int> peak(1000, 1.0);
        for(int i = 0; i < 1000; i++)
        {
            f0.append(0.0f); peak.append(0);
        }
        WorldWaveform *wave1 = new WorldWaveform(Signal(samplingFrequency1, samplingFrequency1), f0, peak, 1.0);
        WorldWaveform *wave2 = new WorldWaveform(Signal(samplingFrequency2, samplingFrequency2), f0, peak, 1.0);
        QList<QSharedPointer<WorldWaveform> > waveforms; waveforms.append(QSharedPointer<WorldWaveform>(wave1)); waveforms.append(QSharedPointer<WorldWaveform>(wave2));

        WaveformFrameInfo element1("", 0.0, 1.0);
        WaveformFrameInfo element2("", 0.0, 1.0);
        QList<WaveformFrameInfo> elements; elements.append(element1); elements.append(element2);

        int fftLength1 = StarSpectrumEstimator::fftLengthFor(samplingFrequency1);
        int fftLength2 = StarSpectrumEstimator::fftLengthFor(samplingFrequency2);
        MockStarSpectrumEstimator *star = new MockStarSpectrumEstimator(fftLength1);
        MockPlatinumResidualCalculator *platinum = new MockPlatinumResidualCalculator(fftLength1);
        auto mockStar = QSharedPointer<StarSpectrumEstimator>(star);
        auto mockPlatinum = QSharedPointer<PlatinumResidualCalculator>(platinum);

        QSharedPointer<double> spectrum1(new double[fftLength1]), spectrum2(new double[fftLength2]), residual1(new double[fftLength1]), residual2(new double[fftLength2]);
        for(int i = 0; i < fftLength1; i++)
        {
            spectrum1.data()[i] = 1.0; residual1.data()[i] = 0.0;
        }
        for(int i = 0; i < fftLength2; i++)
        {
            spectrum2.data()[i] = residual2.data()[i] = i;
        }

        InSequence s;
        EXPECT_CALL(*star, estimate(wave1->signal, 0, 0)).Times(1).WillOnce(Return(spectrum1));
        EXPECT_CALL(*platinum, calculate(wave1->signal, 0, 0, spectrum1)).Times(1).WillOnce(Return(residual1));
        EXPECT_CALL(*star, estimate(wave2->signal, 0, 0)).Times(1).WillOnce(Return(spectrum2));
        EXPECT_CALL(*platinum, calculate(wave2->signal, 0, 0, spectrum2)).Times(1).WillOnce(Return(residual2));

        auto result = TestWorldFrameAnalyzer(mockStar, mockPlatinum).analyze(key, elements, waveforms);

        int index = 0;
        int i;
        for(i = 1; i < fftLength1 / 2; i++)
        {
            index = (double)i * (double)samplingFrequency1 / (double)fftLength1 / (double)samplingFrequency2 * (double)fftLength2;
            if(fftLength2 / 2 <= index + 1)
            {
                break;
            }
            QCOMPARE(result->spectrum.data()[i], spectrum2.data()[index]);
            QCOMPARE(result->residual.data()[i * 2], spectrum2.data()[index * 2]);
            QCOMPARE(result->residual.data()[i * 2 + 1], spectrum2.data()[index * 2 + 1]);
        }
        QCOMPARE(result->spectrum.data()[i], spectrum2.data()[index]);
    }
};

}

DECLARE_TEST(stand::WorldFrameAnalyzerTest)

#endif // WORLDFRAMEANALYZERTEST_H
