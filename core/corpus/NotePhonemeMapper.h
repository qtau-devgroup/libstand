/* NotePhonemeMapper.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef NOTEPHONEMEMAPPER_H
#define NOTEPHONEMEMAPPER_H

#include <QJsonValue>
#include <QList>
#include <QSharedPointer>
#include <QString>

namespace stand
{

/**
 * @brief The NotePhonemeMappingItem class represents a single mapping between note and phoneme.
 * @author Hal@shurabaP
 */
class NotePhonemeMappingItem
{
public:
    NotePhonemeMappingItem(const QString &id, double amplify);
    NotePhonemeMappingItem(const NotePhonemeMappingItem &other);
    NotePhonemeMappingItem &operator =(const NotePhonemeMappingItem &other);

    bool operator ==(const NotePhonemeMappingItem &other) const;

    QString id;
    double amplify;
};

typedef QList<NotePhonemeMappingItem> NotePhonemeMappingList;

/**
 * @brief The NotePhonemeMapper class represents mapping between note and phoneme.
 * @author Hal@shurabaP
 */
class NotePhonemeMapper
{
public:
    NotePhonemeMapper();
    explicit NotePhonemeMapper(const QList<QList<NotePhonemeMappingList> > &elementTable);

    virtual ~NotePhonemeMapper(){ }
    virtual const NotePhonemeMappingList &find(int note, int velocity) const;
    virtual QList<NotePhonemeMappingList> &operator[](int index);
    const QList<QList<NotePhonemeMappingList> > &table() const;
private:
    QList<QList<NotePhonemeMappingList> > elementTable;
    static const NotePhonemeMappingList nullElement;
};

}

#endif // NOTEPHONEMEMAPPER_H
