/* QJsonNotePhonemeMapper.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include <QJsonArray>
#include <QJsonObject>
#include "corpus/NotePhonemeMapper.h"

#include "QJsonNotePhonemeMapper.h"

using namespace stand;

namespace
{
bool isValidItem(const QJsonObject &json)
{
    return json["id"].isString() && json["amplify"].isDouble();
}

NotePhonemeMappingList mappingListFromJson(const QJsonArray &elements)
{
    NotePhonemeMappingList mappingList;
    for(int k = 0; k < elements.size(); k++)
    {
        QSharedPointer<NotePhonemeMappingItem> element;
        elements[k] >> element;
        if(element.isNull())
        {
            continue;
        }
        mappingList.append(*element);
    }
    return mappingList;
}

QList<NotePhonemeMappingList> elementListFromJson(const QJsonArray &velocities)
{
    if(velocities.size() != 128)
    {
        return QList<NotePhonemeMappingList>();
    }
    QList<NotePhonemeMappingList> elementList;
    for(int j = 0; j < velocities.size(); j++)
    {
        if(!velocities.at(j).isArray())
        {
            return QList<NotePhonemeMappingList>();
        }
        elementList.append(mappingListFromJson(velocities.at(j).toArray()));
    }
    return elementList;
}

}

QJsonValue stand::operator <<(QJsonValue &left, const NotePhonemeMappingItem &right)
{
    QJsonObject object;
    object["id"] = right.id;
    object["amplify"] = right.amplify;
    return (left = QJsonValue(object));
}

QSharedPointer<NotePhonemeMappingItem> stand::operator >>(const QJsonValue &left, QSharedPointer<NotePhonemeMappingItem> &right)
{
    if(!left.isObject())
    {
        return QSharedPointer<NotePhonemeMappingItem>();
    }
    QJsonObject object(left.toObject());
    if(!isValidItem(object))
    {
        return QSharedPointer<NotePhonemeMappingItem>();
    }
    return (right = QSharedPointer<NotePhonemeMappingItem>(
                new NotePhonemeMappingItem(object["id"].toString(), object["amplify"].toDouble())));
}


QJsonValue stand::operator <<(QJsonValue &left, const NotePhonemeMapper &right)
{
    QJsonArray table;
    QList<QList<NotePhonemeMappingList> > elementTable(right.table());
    foreach(const auto &elementList, elementTable)
    {
        QJsonArray list;
        foreach(const NotePhonemeMappingList &singleElement, elementList)
        {
            QJsonArray element;
            foreach(const NotePhonemeMappingItem &item, singleElement)
            {
                QJsonValue value;
                value << item;
                element.append(value);
            }
            list.append(element);
        }
        table.append(list);
    }
    return (left = QJsonValue(table));
}

QSharedPointer<NotePhonemeMapper> stand::operator >>(const QJsonValue &left, QSharedPointer<NotePhonemeMapper> &right)
{
    if(!left.isArray())
    {
        return QSharedPointer<NotePhonemeMapper>();
    }
    QJsonArray array(left.toArray());
    if(array.size() != 128)
    {
        return QSharedPointer<NotePhonemeMapper>();
    }

    QList<QList<NotePhonemeMappingList> > elementTable;

    for(int i = 0; i < array.size(); i++)
    {
        if(!array.at(i).isArray())
        {
            return QSharedPointer<NotePhonemeMapper>();
        }
        QList<NotePhonemeMappingList> velocityList(elementListFromJson(array.at(i).toArray()));
        if(velocityList.isEmpty())
        {
            return QSharedPointer<NotePhonemeMapper>();
        }
        elementTable.append(velocityList);
    }
    return (right = QSharedPointer<NotePhonemeMapper>(new NotePhonemeMapper(elementTable)));
}
