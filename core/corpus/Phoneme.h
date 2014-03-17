/* Phoneme.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef PHONEME_H
#define PHONEME_H

#include <QJsonValue>
#include <QList>
#include <QSharedPointer>
#include <QString>

namespace stand
{

/**
 * @brief The Phoneme class is a single element that consits Phoneme.
 * @author Hal@shurabaP
 */
class Phoneme
{
public:
    Phoneme(const QString &filename, double msBegin, double msLength, double msFixedLength, double msPreutterance, double msOverlap);
    Phoneme(const Phoneme &other);
    Phoneme &operator =(const Phoneme &other);
    bool operator ==(const Phoneme &other) const;

    QJsonValue toJson() const;
    static QSharedPointer<Phoneme> fromJson(const QJsonValue &json);

    QString filename;
    double msBegin;
    double msLength;
    double msFixedLength;
    double msPreutterance;
    double msOverlap;

private:
    static bool isValid(const QJsonObject &json);
};

}

#endif // PHONEME_H
