/* Phoneme.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QJsonObject>

#include "Phoneme.h"

using namespace stand;

Phoneme::Phoneme(const QString &filename, double msLeftBlank, double msLength, double msFixedLength, double msPreutterance, double msOverlap) :
    filename(filename), msBegin(msLeftBlank), msLength(msLength), msFixedLength(msFixedLength), msPreutterance(msPreutterance), msOverlap(msOverlap)
{
}

Phoneme::Phoneme(const Phoneme &other) :
    Phoneme(other.filename, other.msBegin, other.msLength, other.msFixedLength, other.msPreutterance, other.msOverlap)
{
}

Phoneme &Phoneme::operator =(const Phoneme &other)
{
    this->filename = other.filename;
    this->msBegin = other.msBegin;
    this->msLength = other.msLength;
    this->msFixedLength = other.msFixedLength;
    this->msPreutterance = other.msPreutterance;
    this->msOverlap = other.msOverlap;
    return *this;
}

bool Phoneme::operator ==(const Phoneme &other) const
{
    return this->filename == other.filename &&
            this->msBegin == other.msBegin &&
            this->msLength == other.msLength &&
            this->msFixedLength == other.msFixedLength &&
            this->msPreutterance == other.msPreutterance &&
            this->msOverlap == other.msOverlap;
}

QJsonValue Phoneme::toJson() const
{
    QJsonObject object;
    object["filename"] = filename;
    object["ms_begin"] = msBegin;
    object["ms_length"] = msLength;
    object["ms_fixed_length"] = msFixedLength;
    object["ms_preutterance"] = msPreutterance;
    object["ms_overlap"] = msOverlap;
    return QJsonValue(object);
}

QSharedPointer<Phoneme> Phoneme::fromJson(const QJsonValue &json)
{
    if(!json.isObject())
    {
        return QSharedPointer<Phoneme>();
    }
    QJsonObject object(json.toObject());
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

    return QSharedPointer<Phoneme>(new Phoneme(filename, msBegin, msLength, msFixedLength, msPreutterance, msOverlap));
}

bool Phoneme::isValid(const QJsonObject &object)
{
    return object["filename"].isString() &&
            object["ms_begin"].isDouble() &&
            object["ms_length"].isDouble() &&
            object["ms_fixed_length"].isDouble() &&
            object["ms_preutterance"].isDouble() &&
            object["ms_overlap"].isDouble();
}
