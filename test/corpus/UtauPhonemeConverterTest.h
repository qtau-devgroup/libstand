/* UtauPhonemeConverterTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef UTAUPHONEMECONVERTERTEST_H
#define UTAUPHONEMECONVERTERTEST_H

#include <QDir>
#include <QObject>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "corpus/UtauPhonemeConverter.h"
#include "corpus/Phoneme.h"
#include "dsp/Signal.h"
#include "helper/MockResourceFactory.h"

#include "AutoTest.h"

using namespace ::testing;

namespace stand
{

class UtauPhonemeCovnerterTest : public QObject
{
    Q_OBJECT
private slots:
    void minus_right_blank_will_be_length()
    {
        double msLeftBlank = 0.0;
        double msFixedLength = 250.0;
        double msRightBlank = -500.0;
        double msPreutterance = 100.0;
        double msOverlap = -100.0;
        QDir dir("hoge");

        UtauPhoneme utau("pronounce", "filename", msLeftBlank, msFixedLength, msRightBlank, msPreutterance, msOverlap);
        auto mockedSignalFactory = new MockResourceFactory<QString, Signal>;
        auto signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(mockedSignalFactory);
        EXPECT_CALL(*mockedSignalFactory, create(_)).Times(0);

        Phoneme p(*(UtauPhonemeConverter().convert(utau, dir, signalFactory)));
        Phoneme expected(QString("hoge/filename"), utau.msLeftBlank, -utau.msRightBlank, utau.msFixedLength, utau.msPreutterance, utau.msOverlap);
        QCOMPARE(p, expected);
    }
    void plus_right_blank_means_offset_from_the_end_of_waveform()
    {
        double msLeftBlank = 0.0;
        double msFixedLength = 250.0;
        double msRightBlank = 500.0;
        double msPreutterance = 100.0;
        double msOverlap = -100.0;
        QDir dir("hoge");

        UtauPhoneme utau("pronounce", "filename", msLeftBlank, msFixedLength, msRightBlank, msPreutterance, msOverlap);
        auto mockedSignalFactory = new MockResourceFactory<QString, Signal>;
        auto signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(mockedSignalFactory);
        Signal signal(44100, 44100);
        EXPECT_CALL(*mockedSignalFactory, create(dir.filePath(utau.filename)))
                .Times(1)
                .WillOnce(Return(signal));

        Phoneme p(*(UtauPhonemeConverter().convert(utau, dir, signalFactory)));
        Phoneme expected(
                    dir.filePath(utau.filename),
                    utau.msLeftBlank,
                    signal.msLength() - utau.msRightBlank - utau.msLeftBlank,
                    utau.msFixedLength,
                    utau.msPreutterance,
                    utau.msOverlap);
        QCOMPARE(p, expected);
    }
};

}

DECLARE_TEST(stand::UtauPhonemeCovnerterTest)

#endif // UTAUPHONEMECONVERTERTEST_H
