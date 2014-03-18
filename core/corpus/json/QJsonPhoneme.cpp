/* QJsonPhoneme.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include <QJsonObject>
#include "corpus/Phoneme.h"

#include "QJsonPhoneme.h"

using namespace stand;

namespace
{

bool isValid(const QJsonObject &object)
{
    return object["filename"].isString() &&
            object["ms_begin"].isDouble() &&
            object["ms_length"].isDouble() &&
            object["ms_fixed_length"].isDouble() &&
            object["ms_preutterance"].isDouble() &&
            object["ms_overlap"].isDouble();
}

}

QJsonValue stand::operator <<(QJsonValue &left, const Phoneme &right)
{
    QJsonObject object;
    object["filename"] = right.filename;
    object["ms_begin"] = right.msBegin;
    object["ms_length"] = right.msLength;
    object["ms_fixed_length"] = right.msFixedLength;
    object["ms_preutterance"] = right.msPreutterance;
    object["ms_overlap"] = right.msOverlap;
    return (left = QJsonValue(object));
}

QSharedPointer<Phoneme> stand::operator >>(const QJsonValue &left, QSharedPointer<Phoneme> &right)
{
    if(!left.isObject())
    {
        return QSharedPointer<Phoneme>();
    }
    QJsonObject object(left.toObject());
    if(!isValid(object))
    {
        return QSharedPointer<Phoneme>();
    }
    QString filename(object["filename"].toString());
    double msBegin(object["ms_begin"].toDouble());
    double msLength(object["ms_length"].toDouble());
    double msFixedLength(object["ms_fixed_length"].toDouble());
    double msPreutterance(object["ms_preutterance"].toDouble());
    double msOverlap(object["ms_overlap"].toDouble());

    return (right = QSharedPointer<Phoneme>(new Phoneme(filename, msBegin, msLength, msFixedLength, msPreutterance, msOverlap)));
}

