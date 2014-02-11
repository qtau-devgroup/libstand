/* UtauOtoHashTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUOTOHASHTEST_H
#define UTAUOTOHASHTEST_H

#include "AutoTest.h"
#include "utau/UtauOtoHash.h"
#include "utau/UtauPhoneme.h"

#include <QList>
#include <QTest>

Q_DECLARE_METATYPE(stand::UtauOtoHash)

namespace stand
{

class UtauOtoHashTest : public QObject
{
    Q_OBJECT
private:
    UtauOtoHash some(const UtauPhoneme &phoneme)
    {
        UtauOtoHash result;
        result.insert(phoneme.pronounce, phoneme);
        return result;
    }
    UtauOtoHash none()
    {
        return UtauOtoHash();
    }

private slots:
    void parseLine_should_parse_one_line_of_utau_oto_ini_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<UtauOtoHash >("expected");

        QTest::newRow("  no alias") << "あ.wav=,98,50,51,100,150" << some(UtauPhoneme("あ", "あ.wav", 98, 50, 51, 100, 150));
        QTest::newRow("with alias") << "あ.wav=- あ,98,50,51,100,150" << some(UtauPhoneme("- あ", "あ.wav", 98, 50, 51, 100, 150));
        QTest::newRow("  invalid1") << "あ.wav=,98,50,51,100" << none();
        QTest::newRow("  invalid2") << "あ.wav=98,50,51,100,150" << none();
        QTest::newRow("  invalid3") << "totally invalid" << none();
    }

    void parseLine_should_parse_one_line_of_utau_oto_ini()
    {
        QFETCH(QString, input);
        QFETCH(UtauOtoHash, expected);
        QStringList ins;
        ins.append(input);

        UtauOtoHashFactory factory(QTextCodec::codecForName("UTF-8"));
        UtauOtoHash actual = factory.parse(ins);
        QCOMPARE(actual, expected);
    }
};

}

DECLARE_TEST(stand::UtauOtoHashTest)

#endif // UTAUOTOHASHTEST_H
