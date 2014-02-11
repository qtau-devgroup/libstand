/* UtauPrefixMapTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUPREFIXMAPTEST_H
#define UTAUPREFIXMAPTEST_H

#include <QTest>

#include "AutoTest.h"
#include "utau/UtauPrefixMap.h"
#include "util/MusicalNote.h"

namespace stand
{

class UtauPrefixMapTest : public QObject
{
    Q_OBJECT
private slots:
    void parse_should_pass_the_test_case()
    {
        QString allLines =
                "invalid line should be ignored\n"
                "\t\t\n"
                "B7\tdir\t↑\n"
                "A#7\tdir\t↑\n"
                "A7\tdir\t↑\n"
                "G#7\tdir\t↑\n"
                "G7\tdir\t↑\n"
                "F#7\tdir\t↑\n"
                "F7\tdir\t↑\n"
                "E7\tdir\t↑\n"
                "D#7\tdir\t↑\n"
                "D7\tdir\t↑\n"
                "C#7\tdir\t↑\n"
                "C7\tdir\t↑\n"
                "B6\tdir\t↑\n"
                "A#6\tdir\t↑\n"
                "A6\tdir\t↑\n"
                "G#6\tdir\t↑\n"
                "G6\tdir\t↑\n"
                "F#6\tdir\t↑\n"
                "F6\tdir\t↑\n"
                "E6\tdir\t↑\n"
                "D#6\tdir\t↑\n"
                "D6\tdir\t↑\n"
                "C#6\tdir\t↑\n"
                "C6\tdir\t↑\n"
                "B5\tdir\t↑\n"
                "A#5\tdir\t↑\n"
                "A5\tdir\t↑\n"
                "G#5\tdir\t↑\n"
                "G5\tdir\t↑\n"
                "F#5\tdir\t↑\n"
                "F5\tdir\t↑\n"
                "E5\tdir\t↑\n"
                "D#5\tdir\t↑\n"
                "D5\tdir\t↑\n"
                "C#5\tdir\t↑\n"
                "C5\tdir\t↑\n"
                "B4\tdir\t↑\n"
                "A#4\tdir\t↑\n"
                "A4\tdir\t\n"
                "G#4\tdir\t\n"
                "G4\tdir\t\n"
                "F#4\tdir\t\n"
                "F4\tdir\t\n"
                "E4\tdir\t\n"
                "D#4\tdir\t\n"
                "D4\tdir\t\n"
                "C#4\tdir\t↓\n"
                "C4\tdir\t↓\n"
                "B3\tdir\t↓\n"
                "A#3\tdir\t↓\n"
                "A3\tdir\t↓\n"
                "G#3\tdir\t↓\n"
                "G3\tdir\t↓\n"
                "F#3\tdir\t↓\n"
                "F3\tdir\t↓\n"
                "E3\tdir\t↓\n"
                "D#3\tdir\t↓\n"
                "D3\tdir\t↓\n"
                "C#3\tdir\t↓\n"
                "C3\tdir\t↓\n"
                "B2\tdir\t↓\n"
                "A#2\tdir\t↓\n"
                "A2\tdir\t↓\n"
                "G#2\tdir\t↓\n"
                "G2\tdir\t↓\n"
                "F#2\tdir\t↓\n"
                "F2\tdir\t↓\n"
                "E2\tdir\t↓\n"
                "D#2\tdir\t↓\n"
                "D2\tdir\t↓\n"
                "C#2\tdir\t↓\n"
                "C2\tdir\t↓\n"
                "B1\tdir\t↓\n"
                "A#1\tdir\t↓\n"
                "A1\tdir\t↓\n"
                "G#1\tdir\t↓\n"
                "G1\tdir\t↓\n"
                "F#1\tdir\t↓\n"
                "F1\tdir\t↓\n"
                "E1\tdir\t↓\n"
                "D#1\tdir\t↓\n"
                "D1\tdir\t↓\n"
                "C#1\tdir\t↓\n"
                "C1\tdir\t↓\n";
        QStringList testCase = allLines.split("\n");
        UtauPrefixMap prefixMap(UtauPrefixMap::parse(testCase));
        bool notes[128];
        for(int i = 0; i < 128; i++)
        {
            notes[i] = false;
        }
        foreach(const QString &line, testCase)
        {
            QStringList params = line.split("\t");
            if(params.size() != 3)
            {
                continue;
            }
            int note = MusicalNote::noteNumber(params[0]);
            if(note < 0 || 127 < note)
            {
                continue;
            }
            notes[note] = true;
            QString dir = params[1];
            QString postfix = params[2];
            QCOMPARE(prefixMap.at(note).directory, dir);
            QCOMPARE(prefixMap.at(note).suffix, postfix);
        }
        for(int i = 0; i < 128; i++)
        {
            if(notes[i])
            {
                continue;
            }
            QCOMPARE(prefixMap.at(i).directory, QString(""));
            QCOMPARE(prefixMap.at(i).suffix, QString(""));
        }
    }
};
}

#endif // UTAUPREFIXMAPTEST_H
