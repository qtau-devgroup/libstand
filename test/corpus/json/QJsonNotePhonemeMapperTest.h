/* QJsonNotePhonemeMapperTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONNOTEPHONEMEMAPPERTEST_H
#define QJSONNOTEPHONEMEMAPPERTEST_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QTest>

#include "corpus/NotePhonemeMapper.h"
#include "corpus/json/QJsonNotePhonemeMapper.h"
#include "util/JsonSerializer.h"

#include "AutoTest.h"

#define ITEM "{\"id\":\"1\",\"amplify\":1.25}"

namespace stand
{

namespace
{

const char itemRaw[] =
        "{"
        "  \"id\" : \"1\","
        "  \"amplify\" : 1.25"
        "}";
const QString itemRawString(itemRaw);
const QJsonValue itemJson(QJsonDocument::fromJson(QByteArray(itemRaw)).object());
NotePhonemeMappingItem item("1", 1.25);

}

class QJsonNotePhonemeMapperTest : public QObject
{
    Q_OBJECT
private slots:
    void json_serialize_should_succeed_jsonizing_item()
    {
        QCOMPARE(JsonSerializer::toJson(item), itemJson);
    }
    void json_unserialize_should_succeed_desirializing_item()
    {
        QCOMPARE(*(JsonSerializer::fromJson<NotePhonemeMappingItem>(itemJson)), item);
    }

    void json_unserialize_should_succeed_desirializing_and_serializing_item()
    {
        QList<QList<NotePhonemeMappingList> > table;
        for(int i = 0; i < 128; i++)
        {
            QList<NotePhonemeMappingList> list;
            for(int j = 0; j < 128; j++)
            {
                NotePhonemeMappingList element;
                element.append(NotePhonemeMappingItem(QString::number(i), j));
                element.append(NotePhonemeMappingItem(QString(""), 0.0));
                list.append(element);
            }
            table.append(list);
        }
        NotePhonemeMapper expected(table);
        auto actual = JsonSerializer::fromJson<NotePhonemeMapper>(JsonSerializer::toJson(expected));
        for(int i = 0; i < 128; i++)
        {
            for(int j = 0; j < 128; j++)
            {
                for(int k = 0; k < 2; k++)
                {
                    QCOMPARE(actual->table()[i][j][k], expected.table()[i][j][k]);
                }
            }
        }
    }
};

}

DECLARE_TEST(stand::QJsonNotePhonemeMapperTest)

#endif // QJSONNOTEPHONEMEMAPPERTEST_H
