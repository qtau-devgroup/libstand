/* QJsonPhonemeRepository.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include <QJsonObject>
#include "corpus/PhonemeRepository.h"
#include "corpus/json/QJsonPhoneme.h"

#include "QJsonPhonemeRepository.h"

using namespace stand;

QJsonValue stand::operator <<(QJsonValue &left, const PhonemeRepository &right)
{
    QJsonObject object;
    foreach(const QString &key, right.keys())
    {
        QJsonValue value;
        value << *(right.find(key));
        object[key] = value;
    }
    return (left = QJsonValue(object));
}

QSharedPointer<ResourceRepository<QString, Phoneme> > stand::operator >>(const QJsonValue &left, QSharedPointer<ResourceRepository<QString, Phoneme> > &right)
{
    if(!left.isObject())
    {
        return QSharedPointer<ResourceRepository<QString, Phoneme> >();
    }
    QSharedPointer<ResourceRepository<QString, Phoneme> > repository(new PhonemeRepository);
    QJsonObject object(left.toObject());
    for(auto it = object.begin(); it != object.end(); it++)
    {
        QJsonValue value(it.value());
        QSharedPointer<Phoneme> phoneme;
        value >> phoneme;
        repository->add(it.key(), phoneme);
    }
    return (right = repository);
}
