/* QJsonWaveformCorpus.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef QJSONWAVEFORMCORPUS_H
#define QJSONWAVEFORMCORPUS_H

#include <QJsonValue>
#include <QSharedPointer>

namespace stand
{

template <class K, class V> class ResourceRepository;
class PhonemeKey;
class WaveformCorpus;
class WaveformFrameInfo;
typedef QList<WaveformFrameInfo> WaveformFrameInfoList;

QJsonValue operator <<(QJsonValue &left, const WaveformCorpus &right);
QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > operator >>(
        const QJsonValue &left, QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > &right);

}

#endif // QJSONWAVEFORMCORPUS_H
