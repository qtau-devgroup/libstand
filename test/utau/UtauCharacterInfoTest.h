/* UtauCharacterInfoTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUCHARACTERINFOTEST_H
#define UTAUCHARACTERINFOTEST_H

#include <QTest>

#include "AutoTest.h"
#include "utau/UtauCharacterInfo.h"

namespace stand
{

class UtauCharacterInfoTest : public QObject
{
    Q_OBJECT
private slots:
    void parse_should_properly_parse_QStringList()
    {
        QString text =
                "name  =  i_am_a_name\n"
                "\n"
                "    image =     image.png\n"
                "\n"
                "invalid line should be ignored\n"
                "\n"
                "\tsample =      sample.mp3\n"
                "\t\t     author=i am an author\n"
                "author=hoge=foo\n"
                "\n"
                "web=     http://www.example.com"
                "\n"
                "\n";
        QStringList testCase = text.split("\n");
        UtauCharacterInfo info(UtauCharacterInfo::parse(testCase));
        QCOMPARE(info.name, QString("i_am_a_name"));
        QCOMPARE(info.image, QFileInfo("image.png"));
        QCOMPARE(info.sample, QFileInfo("sample.mp3"));
        QCOMPARE(info.author, QString("i am an author"));
        QCOMPARE(info.web, QUrl("http://www.example.com"));
    }

    void parse_should_return_empty_info()
    {
        QString text = "";
        QStringList testCase = text.split("\n");
        UtauCharacterInfo info(UtauCharacterInfo::parse(testCase));
        QCOMPARE(info.name, QString(""));
        QCOMPARE(info.image, QFileInfo(""));
        QCOMPARE(info.sample, QFileInfo(""));
        QCOMPARE(info.author, QString(""));
        QCOMPARE(info.web, QUrl(""));

    }
};

}

DECLARE_TEST(stand::UtauCharacterInfoTest)

#endif // UTAUCHARACTERINFOTEST_H
