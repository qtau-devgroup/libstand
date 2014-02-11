/* CorpusMeta.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef COPUSMETA_H
#define COPUSMETA_H

#include <QString>
#include <QUrl>

namespace stand
{

class CorpusMeta
{
public:
    CorpusMeta(const QString &name, const QString &imagePath, const QString &samplePath, const QString &author, const QUrl &web);
    CorpusMeta(const CorpusMeta &other);
    CorpusMeta &operator =(const CorpusMeta &other);

    QString name;
    QString imagePath;
    QString samplePath;
    QString author;
    QUrl web;
};

}

#endif // COPUSMETA_H
