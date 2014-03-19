/* QJsonPhonemeRepositoryTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONPHONEMEREPOSITORYTEST_H
#define QJSONPHONEMEREPOSITORYTEST_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "corpus/PhonemeRepository.h"
#include "corpus/json/QJsonPhonemeRepository.h"
#include "util/JsonSerializer.h"

#include "AutoTest.h"

namespace stand
{
namespace
{
const char raw[] =
    "{"
    "  \"あ\" : {"
    "    \"filename\" : \"あ.wav\","
    "    \"ms_begin\" : 1.0,"
    "    \"ms_length\" : 2.0,"
    "    \"ms_fixed_length\" : 3.0,"
    "    \"ms_preutterance\" : 4.0,"
    "    \"ms_overlap\" : 5.0,"
    "  }, "
    "  \"い\" : "
    "    \"filename\" : \"い.wav\","
    "    \"ms_begin\" : 5.0,"
    "    \"ms_length\" : 4.0,"
    "    \"ms_fixed_length\" : 3.0,"
    "    \"ms_preutterance\" : 2.0,"
    "    \"ms_overlap\" : 1.0,"
    "  },"
    "  \"う\" : "
    "    \"filename\" : \"う.wav\","
    "    \"ms_begin\" : 5.0,"
    "    \"ms_length\" : 4.0,"
    "    \"ms_preutterance\" : 2.0,"
    "    \"ms_overlap\" : 1.0,"
    "  }"
    "}";

const QJsonValue json(QJsonDocument::fromJson(raw).object());
const Phoneme phonemeA("あ.wav", 1.0, 2.0, 3.0, 4.0, 5.0);
const Phoneme phonemeI("い.wav", 5.0, 4.0, 3.0, 2.0, 1.0);

}

class QJsonPhonemeRepositoryTest : public QObject
{
    Q_OBJECT
private slots:
    void json_serialize_should_succeed_in()
    {
        PhonemeRepository repository;
        repository.add("あ", QSharedPointer<Phoneme>(new Phoneme(phonemeA)));
        repository.add("い", QSharedPointer<Phoneme>(new Phoneme(phonemeI)));
        QCOMPARE(JsonSerializer::toJson(repository), json);
    }
    void json_deserialize_should_succeed_in()
    {
        QCOMPARE(*(JsonSerializer::fromJson<ResourceRepository<QString, Phoneme> >(json)->find(QString("あ"))), phonemeA);
        QCOMPARE(*(JsonSerializer::fromJson<ResourceRepository<QString, Phoneme> >(json)->find(QString("い"))), phonemeI);
        QCOMPARE((JsonSerializer::fromJson<ResourceRepository<QString, Phoneme> >(json)->find(QString("う")).isNull()), true);
    }
};
}

#endif // QJSONPHONEMEREPOSITORYTEST_H
