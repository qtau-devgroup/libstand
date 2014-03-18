/* QJsonCorpusMeta.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONCORPUSMETA_H
#define QJSONCORPUSMETA_H

#include <QJsonValue>
#include <QSharedPointer>

namespace stand
{

class CorpusMeta;

QJsonValue operator <<(QJsonValue &left, const CorpusMeta &right);
QSharedPointer<CorpusMeta> operator >>(const QJsonValue &left, QSharedPointer<CorpusMeta> &right);

}

#endif // QJSONCORPUSMETA_H
