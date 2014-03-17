/* NotePhonemeMapper.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QJsonArray>
#include <QJsonObject>

#include "NotePhonemeMapper.h"

using namespace stand;

const NotePhonemeMappingList NotePhonemeMapper::nullElement;

NotePhonemeMappingItem::NotePhonemeMappingItem(const QString &id, double amplify) :
    id(id), amplify(amplify)
{
}

NotePhonemeMappingItem::NotePhonemeMappingItem(const NotePhonemeMappingItem &other) :
    NotePhonemeMappingItem(other.id, other.amplify)
{
}

NotePhonemeMappingItem &NotePhonemeMappingItem::operator =(const NotePhonemeMappingItem &other)
{
    id = other.id;
    amplify = other.amplify;
    return *this;
}

bool NotePhonemeMappingItem::operator ==(const NotePhonemeMappingItem &other)
{
    return id == other.id &&
            amplify == other.amplify;
}

QJsonValue NotePhonemeMappingItem::toJson() const
{
    QJsonObject object;
    object["id"] = id;
    object["amplify"] = amplify;
    return QJsonValue(object);
}

QSharedPointer<NotePhonemeMappingItem> NotePhonemeMappingItem::fromJson(const QJsonValue &json)
{
    if(!json.isObject())
    {
        return QSharedPointer<NotePhonemeMappingItem>();
    }
    QJsonObject object(json.toObject());
    if(!isValid(object))
    {
        return QSharedPointer<NotePhonemeMappingItem>();
    }
    return QSharedPointer<NotePhonemeMappingItem>(
                new NotePhonemeMappingItem(object["id"].toString(), object["amplify"].toDouble())
            );
}

bool NotePhonemeMappingItem::isValid(const QJsonObject &json)
{
    return json["id"].isString() && json["amplify"].isDouble();
}

NotePhonemeMapper::NotePhonemeMapper()
{
    elementTable.reserve(128);
    for(int i = 0; i < 128; i++)
    {
        elementTable.append(QList<NotePhonemeMappingList>());
        elementTable[i].reserve(128);
        for(int j = 0; j < 128; j++)
        {
            elementTable[i].append(NotePhonemeMappingList());
        }
    }
}

NotePhonemeMapper::NotePhonemeMapper(const QList<QList<NotePhonemeMappingList> > &elementTable) :
    elementTable(elementTable)
{
}

const NotePhonemeMappingList &NotePhonemeMapper::find(int note, int velocity) const
{
    if(elementTable.isEmpty())
    {
        return nullElement;
    }
    note = qMax(0, qMin(elementTable.size(), note));
    if(elementTable[note].isEmpty())
    {
        return nullElement;
    }
    velocity = qMax(0, qMin(elementTable[note].size(), velocity));

    return elementTable[note][velocity];
}

QList<NotePhonemeMappingList> &NotePhonemeMapper::operator [](int index)
{
    return elementTable[index];
}

QJsonValue NotePhonemeMapper::toJson() const
{
    QJsonArray table;
    foreach(const auto &elementList, elementTable)
    {
        QJsonArray list;
        foreach(const NotePhonemeMappingList &singleElement, elementList)
        {
            QJsonArray element;
            foreach(const NotePhonemeMappingItem &item, singleElement)
            {
                element.append(item.toJson());
            }
            list.append(element);
        }
        table.append(list);
    }
    return QJsonValue(table);
}

QSharedPointer<NotePhonemeMapper> NotePhonemeMapper::fromJson(const QJsonValue &json)
{
    if(!json.isArray())
    {
        return QSharedPointer<NotePhonemeMapper>();
    }
    QJsonArray array(json.toArray());
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
    return QSharedPointer<NotePhonemeMapper>(new NotePhonemeMapper(elementTable));
}

QList<NotePhonemeMappingList> NotePhonemeMapper::elementListFromJson(const QJsonArray &velocities)
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

NotePhonemeMappingList NotePhonemeMapper::mappingListFromJson(const QJsonArray &elements)
{
    NotePhonemeMappingList mappingList;
    for(int k = 0; k < elements.size(); k++)
    {
        QSharedPointer<NotePhonemeMappingItem> element(NotePhonemeMappingItem::fromJson(elements.at(k)));
        if(element.isNull())
        {
            continue;
        }
        mappingList.append(*element);
    }
    return mappingList;
}
