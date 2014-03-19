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

bool NotePhonemeMappingItem::operator ==(const NotePhonemeMappingItem &other) const
{
    return id == other.id && amplify == other.amplify;
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

const QList<QList<NotePhonemeMappingList> > &NotePhonemeMapper::table() const
{
    return elementTable;
}
