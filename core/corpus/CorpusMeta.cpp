/* CorpusMeta.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QJsonObject>

#include "CorpusMeta.h"

using namespace stand;

CorpusMeta::CorpusMeta(const QString &name, const QString &imagePath, const QString &samplePath, const QString &author, const QUrl &web) :
    name(name), imagePath(imagePath), samplePath(samplePath), author(author), web(web)
{
}

CorpusMeta::CorpusMeta(const CorpusMeta &other) :
    CorpusMeta(other.name, other.imagePath, other.samplePath, other.author, other.web)
{
}

CorpusMeta &CorpusMeta::operator =(const CorpusMeta &other)
{
    name = other.name;
    imagePath = other.imagePath;
    samplePath = other.samplePath;
    author = other.author;
    web = other.web;
    return *this;
}

QJsonValue CorpusMeta::toJson() const
{
    QJsonObject object;
    object["name"] = name;
    object["image_path"] = imagePath;
    object["sample_path"] = samplePath;
    object["author"] = author;
    object["web"] = web.toString();
    return QJsonValue(object);
}

QSharedPointer<CorpusMeta> CorpusMeta::fromJson(const QJsonValue &json)
{
    if(!json.isObject())
    {
        return QSharedPointer<CorpusMeta>();
    }
    QJsonObject object(json.toObject());
    if(!isValid(object))
    {
        return QSharedPointer<CorpusMeta>();
    }
    QString name(object["name"].toString());
    QString imagePath(object["image_path"].toString());
    QString samplePath(object["sample_path"].toString());
    QString author(object["author"].toString());
    QUrl web(object["web"].toString());

    return QSharedPointer<CorpusMeta>(new CorpusMeta(name, imagePath, samplePath, author, web));
}

bool CorpusMeta::isValid(const QJsonObject &json)
{
    return json["name"].isString() &&
        json["image_path"].isString() &&
        json["sample_path"].isString() &&
        json["author"].isString() &&
        json["web"].isString();
}

