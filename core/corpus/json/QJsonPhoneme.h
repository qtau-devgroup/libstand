/* QJsonPhoneme.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONPHONEME_H
#define QJSONPHONEME_H
#include <QJsonValue>
#include <QSharedPointer>

namespace stand
{

class Phoneme;

QJsonValue operator <<(QJsonValue &left, const Phoneme &phoneme);

QSharedPointer<Phoneme> operator>>(const QJsonValue &left, QSharedPointer<Phoneme> &right);

}

#endif // QJSONPHONEME_H
