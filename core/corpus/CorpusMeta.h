/* CorpusMeta.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef COPUSMETA_H
#define COPUSMETA_H

#include <QString>
#include <QUrl>

namespace stand
{

/**
 * @brief The CorpusMeta class represents a meta information for STAND corpus.
 * @author Hal@shurabaP
 */
class CorpusMeta
{
public:
    /**
     * @brief CorpusMeta
     * @param name is a name of the corpus.
     * @param imagePath is an icon image path.
     * @param samplePath is an example samplme path.
     * @param author
     * @param web is a URL for the corpus.
     */
    CorpusMeta(const QString &name, const QString &imagePath, const QString &samplePath, const QString &author, const QUrl &web);
    CorpusMeta(const CorpusMeta &other);
    CorpusMeta &operator =(const CorpusMeta &other);

    bool operator==(const CorpusMeta &toher) const;

    QString name;
    QString imagePath;
    QString samplePath;
    QString author;
    QUrl web;
};

}

#endif // COPUSMETA_H
