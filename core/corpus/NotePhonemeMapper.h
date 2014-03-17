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

    bool operator ==(const NotePhonemeMappingItem &other);

    QJsonValue toJson() const;
    static QSharedPointer<NotePhonemeMappingItem> fromJson(const QJsonValue &json);

    QString id;
    double amplify;
private:
    static bool isValid(const QJsonObject &json);
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

    QJsonValue toJson() const;
    static QSharedPointer<NotePhonemeMapper> fromJson(const QJsonValue &json);
private:
    static QList<NotePhonemeMappingList> elementListFromJson(const QJsonArray &velocities);
    static NotePhonemeMappingList mappingListFromJson(const QJsonArray &elements);

    QList<QList<NotePhonemeMappingList> > elementTable;
    static const NotePhonemeMappingList nullElement;
};

}

#endif // NOTEPHONEMEMAPPER_H
