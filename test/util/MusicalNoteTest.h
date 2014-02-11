/* MusicalNoteTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef MUSICALNOTETEST_H
#define MUSICALNOTETEST_H

#include <QObject>
#include <QTest>

#include "AutoTest.h"
#include "util/MusicalNote.h"

namespace stand
{

namespace
{
const QString notes[] = {
    "C-2", "C-2#", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2",
    "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1",
    "C0",  "C#0",  "D0",  "D#0",  "E0",  "F0",  "F#0",  "G0",  "G#0",  "A0",  "A#0",  "B0",
    "C1",  "C#1",  "D1",  "D#1",  "E1",  "F1",  "F#1",  "G1",  "G#1",  "A1",  "A#1",  "B1",
    "C2",  "C#2",  "D2",  "D#2",  "E2",  "F2",  "F#2",  "G2",  "G#2",  "A2",  "A#2",  "B2",
    "C3",  "C#3",  "D3",  "D#3",  "E3",  "F3",  "F#3",  "G3",  "G#3",  "A3",  "A#3",  "B3",
    "C4",  "C#4",  "D4",  "D#4",  "E4",  "F4",  "F#4",  "G4",  "G#4",  "A4",  "A#4",  "B4",
    "C5",  "C#5",  "D5",  "D#5",  "E5",  "F5",  "F#5",  "G5",  "G#5",  "A5",  "A#5",  "B5",
    "C6",  "C#6",  "D6",  "D#6",  "E6",  "F6",  "F#6",  "G6",  "G#6",  "A6",  "A#6",  "B6",
    "C7",  "C#7",  "D7",  "D#7",  "E7",  "F7",  "F#7",  "G7",  "G#7",  "A7",  "A#7",  "B7",
    "C8",  "C#8",  "D8",  "D#8",  "E8",  "F8",  "F#8",  "G8"
};
}

class MusicalNoteTest : public QObject
{
    Q_OBJECT
private slots:
    void frequency_from_note_should_pass_all_test_cases_data()
    {
        QTest::addColumn<double>("input");
        QTest::addColumn<double>("expected");
        QTest::newRow("C4") << 60.0 << 261.6255653005986;
        QTest::newRow("C+4") << 61.0 << 277.1826309768721;
        QTest::newRow("D4") << 62.0 << 293.6647679174076;
        QTest::newRow("D+4") << 63.0 << 311.12698372208087;
        QTest::newRow("E4") << 64.0 << 329.6275569128699;
        QTest::newRow("F4") << 65.0 << 349.2282314330039;
        QTest::newRow("F+4") << 66.0 << 369.9944227116344;
        QTest::newRow("G4") << 67.0 << 391.99543598174927;
        QTest::newRow("G+4") << 68.0 << 415.3046975799451;
        QTest::newRow("A4") << 69.0 << 440.0;
        QTest::newRow("A+4") << 70.0 << 466.1637615180899;
        QTest::newRow("B4") << 71.0 << 493.8833012561241;
    }

    void frequency_from_note_should_pass_all_test_cases()
    {
        QFETCH(double, input);
        QFETCH(double, expected);

        QCOMPARE(MusicalNote::frequencyFromNote(input), expected);
    }

    void note_from_frequency_should_pass_all_test_cases_data()
    {
        QTest::addColumn<double>("input");
        QTest::addColumn<double>("expected");
        QTest::newRow("C4") << 261.6255653005986 << 60.0;
        QTest::newRow("C+4") << 277.1826309768721 << 61.0;
        QTest::newRow("D4") << 293.6647679174076 << 62.0;
        QTest::newRow("D+4") << 311.12698372208087 << 63.0;
        QTest::newRow("E4") << 329.6275569128699 << 64.0;
        QTest::newRow("F4") << 349.2282314330039 << 65.0;
        QTest::newRow("F+4") << 369.9944227116344 << 66.0;
        QTest::newRow("G4") << 391.99543598174927 << 67.0;
        QTest::newRow("G+4") << 415.3046975799451 << 68.0;
        QTest::newRow("A4") << 440.0 << 69.0;
        QTest::newRow("A+4") << 466.1637615180899 << 70.0;
        QTest::newRow("B4") << 493.8833012561241 << 71.0;
    }

    void note_from_frequency_should_pass_all_test_cases()
    {
        QFETCH(double, input);
        QFETCH(double, expected);

        QCOMPARE(MusicalNote::noteFromFrequency(input), expected);
    }


    void noteNumber_should_pass_the_test_case()
    {
        for(int i = 0; i < 128; i++)
        {
            QCOMPARE(i, MusicalNote::noteNumber(notes[i]));
        }
        QCOMPARE(-1, MusicalNote::noteNumber("invalid"));
        QCOMPARE(-1, MusicalNote::noteNumber("B-3")); // flat not supported
        QCOMPARE(-1, MusicalNote::noteNumber("A+2")); // + should be #
        QCOMPARE(-1, MusicalNote::noteNumber("a#2")); // should be Capital
        QCOMPARE(-1, MusicalNote::noteNumber(""));
    }

    void noteName_should_pass_the_test_case()
    {
        for(int i = 0; i < 128; i++)
        {
            QCOMPARE(notes[i], MusicalNote::noteName(i));
        }
        QCOMPARE(QString(""), MusicalNote::noteName(-1));
        QCOMPARE(QString(""), MusicalNote::noteName(128));
    }
};

}

DECLARE_TEST(stand::MusicalNoteTest)

#endif // MUSICALNOTETEST_H
