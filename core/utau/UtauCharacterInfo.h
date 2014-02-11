/* UtauCharacterInfo.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUCHARACTERINFO_H
#define UTAUCHARACTERINFO_H

#include <QFileInfo>
#include <QString>
#include <QUrl>

namespace stand
{

/**
 * @brief The UtauCharacterInfo class represents character.txt of UTAU voicebanks.
 * @author Hal@shurabaP
 */
class UtauCharacterInfo
{
public:
    explicit UtauCharacterInfo(const QStringList &lines) :
        UtauCharacterInfo(parse(lines)){ }
    UtauCharacterInfo(const QString &name, const QFileInfo &image, const QFileInfo &sample, const QString &author, const QUrl &web) :
        name(name), image(image), sample(sample), author(author), web(web){ }
    UtauCharacterInfo(const UtauCharacterInfo &info) :
        UtauCharacterInfo(info.name, info.image, info.sample, info.author, info.web){ }
    UtauCharacterInfo &operator =(const UtauCharacterInfo &info);

    /**
     * @brief parse parses character.txt.
     * @param lines to parse.
     * @return parsed UtauCharacterInfo
     */
    static UtauCharacterInfo parse(const QStringList &lines);

    QString name;
    QFileInfo image;
    QFileInfo sample;
    QString author;
    QUrl web;
};

}

#endif // UTAUCHARACTERINFO_H
