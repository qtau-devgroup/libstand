/* QJsonPhonemeRepository.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONPHONEMEREPOSITORY_H
#define QJSONPHONEMEREPOSITORY_H

#include <QJsonValue>
#include <QSharedPointer>

namespace stand
{

class Phoneme;
class PhonemeRepository;
template <class K, class V> class ResourceRepository;

QJsonValue operator <<(QJsonValue &left, const PhonemeRepository &right);
QSharedPointer<ResourceRepository<QString, Phoneme> > operator >>(const QJsonValue &left, QSharedPointer<ResourceRepository<QString, Phoneme> > &right);

}

#endif // QJSONPHONEMEREPOSITORY_H
