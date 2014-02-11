/* UtauCharacterInfo.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QStringList>

#include "UtauCharacterInfo.h"

using namespace stand;

UtauCharacterInfo &UtauCharacterInfo::operator =(const UtauCharacterInfo &info)
{
    this->name = info.name;
    this->image = info.image;
    this->sample = info.sample;
    this->author = info.author;
    this->web = info.web;
    return (*this);
}

UtauCharacterInfo UtauCharacterInfo::parse(const QStringList &lines)
{
    QString name;
    QFileInfo image("");
    QFileInfo sample("");
    QString author;
    QUrl web;
    foreach(const QString &line, lines)
    {
        QStringList params = line.split("=");
        if(params.size() != 2)
        {
            continue;
        }
        params[0] = params[0].trimmed();
        params[1] = params[1].trimmed();
        if(params[0] == "name")
        {
            name = params[1];
        }
        else if(params[0] == "image")
        {
            image = QFileInfo(params[1]);
        }
        else if(params[0] == "sample")
        {
            sample = QFileInfo(params[1]);
        }
        else if(params[0] == "author")
        {
            author = params[1];
        }
        else if(params[0] == "web")
        {
            web = QUrl(params[1]);
        }
    }
    return UtauCharacterInfo(name, image, sample, author, web);
}
