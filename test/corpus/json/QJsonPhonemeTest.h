/* QJsonPhonemeTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONPHONEMETEST_H
#define QJSONPHONEMETEST_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTest>
#include "corpus/Phoneme.h"
#include "corpus/json/QJsonPhoneme.h"
#include "util/JsonSerializer.h"

#include "AutoTest.h"

namespace stand
{

namespace
{
const char raw[] =
        "{"
        "  \"filename\" : \"hoge.wav\","
        "  \"ms_begin\" : 1.0,"
        "  \"ms_length\" : 2.0,"
        "  \"ms_fixed_length\" : 3.0,"
        "  \"ms_preutterance\" : 4.0,"
        "  \"ms_overlap\" : 5.0,"
        "}";

const char invalid[] =
        "{"
        "  \"filename\" : \"hoge.wav\","
        "  \"ms_begin\" : 1.0,"
        "  \"ms_fixed_length\" : 3.0,"
        "  \"ms_preutterance\" : 4.0,"
        "  \"ms_overlap\" : 5.0,"
        "}";

const QJsonValue json(QJsonDocument::fromJson(raw).object());
const Phoneme phoneme("hoge.wav", 1.0, 2.0, 3.0, 4.0, 5.0);
const QJsonValue invalidJson(QJsonDocument::fromJson(invalid).object());
}

class QJsonPhonemeTest : public QObject
{
    Q_OBJECT
private slots:
    void json_serialize_should_succeed_in()
    {
        QCOMPARE(JsonSerializer::toJson(phoneme), json);
    }

    void json_deserialize_should_succeed_in()
    {
        QCOMPARE(*JsonSerializer::fromJson<Phoneme>(json), phoneme);
    }

    void json_deserialize_should_fail_in()
    {
        QCOMPARE(JsonSerializer::fromJson<Phoneme>(invalidJson).isNull(), true);
    }
};

}

#endif // QJSONPHONEMETEST_H
