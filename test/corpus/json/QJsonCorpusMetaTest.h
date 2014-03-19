/* QJsonCorpusMetaTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONCORPUSMETATEST_H
#define QJSONCORPUSMETATEST_H

#include <QTest>
#include <QJsonDocument>
#include <QJsonObject>

#include "corpus/CorpusMeta.h"
#include "corpus/json/QJsonCorpusMeta.h"
#include "util/JsonSerializer.h"

#include "AutoTest.h"

namespace stand
{
namespace
{

const char raw[] =
    "{"
    "  \"name\" : \"i_am_name\","
    "  \"image_path\" : \"i_am_image_path\","
    "  \"sample_path\" : \"i_am_sample_path\","
    "  \"author\" : \"i_am_an_author\","
    "  \"web\" : \"http://www.example.com/\""
    "}";

const char extra[] =
    "{"
    "  \"name\" : \"i_am_name\","
    "  \"image_path\" : \"i_am_image_path\","
    "  \"sample_path\" : \"i_am_sample_path\","
    "  \"extra\" : \"data\","
    "  \"author\" : \"i_am_an_author\","
    "  \"web\" : \"http://www.example.com/\""
    "}";

const char invalid[] =
    "{"
    "  \"here\" : \"is\","
    "  \"invalid\" : \"json\""
    "}";

static CorpusMeta meta(QString("i_am_name"), QString("i_am_image_path"), QString("i_am_sample_path"), QString("i_am_an_author"), QUrl("http://www.example.com/"));
QJsonValue json(QJsonDocument::fromJson(QByteArray(raw)).object());
QJsonValue extraJson(QJsonDocument::fromJson(QByteArray(extra)).object());
QJsonValue invalidJson(QJsonDocument::fromJson(QByteArray(invalid)).object());

}

class QJsonCorpusMetaTest : public QObject
{
    Q_OBJECT
private:
private slots:
    void json_serialize_should_succeed_in()
    {
        // toJson is basically rare to fail because it simply puts data into JsonObject.
        QCOMPARE(JsonSerializer::toJson(meta), json);
    }

    void json_deserialize_should_succeed_in()
    {
        QCOMPARE(*(JsonSerializer::fromJson<CorpusMeta>(json)), meta);
    }

    void json_deserialize_should_succeed_event_if_extra_data_exist_in()
    {
        QCOMPARE(*(JsonSerializer::fromJson<CorpusMeta>(extraJson)), meta);
    }

    void json_deserialize_should_fail_in()
    {
        QCOMPARE(JsonSerializer::fromJson<CorpusMeta>(invalidJson).isNull(), true);
    }
};

}

DECLARE_TEST(stand::QJsonCorpusMetaTest)

#endif // QJSONCORPUSMETATEST_H
