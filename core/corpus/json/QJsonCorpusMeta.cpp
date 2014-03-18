/* QJsonCorpusMeta.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include <QJsonObject>
#include "corpus/CorpusMeta.h"

#include "QJsonCorpusMeta.h"

using namespace stand;

namespace
{
bool isValid(const QJsonObject &json)
{
    return json["name"].isString() &&
        json["image_path"].isString() &&
        json["sample_path"].isString() &&
        json["author"].isString() &&
        json["web"].isString();
}

}

QJsonValue stand::operator <<(QJsonValue &left, const CorpusMeta &right)
{
    QJsonObject object;
    object["name"] = right.name;
    object["image_path"] = right.imagePath;
    object["sample_path"] = right.samplePath;
    object["author"] = right.author;
    object["web"] = right.web.toString();
    return (left = QJsonValue(object));
}

QSharedPointer<CorpusMeta> stand::operator >>(const QJsonValue &left, QSharedPointer<CorpusMeta> &right)
{
    if(!left.isObject())
    {
        return QSharedPointer<CorpusMeta>();
    }
    QJsonObject object(left.toObject());
    if(!isValid(object))
    {
        return QSharedPointer<CorpusMeta>();
    }
    QString name(object["name"].toString());
    QString imagePath(object["image_path"].toString());
    QString samplePath(object["sample_path"].toString());
    QString author(object["author"].toString());
    QUrl web(object["web"].toString());

    return (right = QSharedPointer<CorpusMeta>(new CorpusMeta(name, imagePath, samplePath, author, web)));
}
