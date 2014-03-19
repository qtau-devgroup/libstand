/* JsonSerializer.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QJsonValue>
#include <QSharedPointer>
#include <QVariant>

namespace stand
{

/**
 * @brief The JsonSerializer class serializes data.
 * @author Hal@shurabaP
 */
class JsonSerializer
{
public:
    /**
     * @brief toJson makes QJsonValue from `t`.
     *        Type parameter `T` should have the function below:
     *        QJsonValue operator << (QJsonValue &left, const T &right);
     * @param t
     * @return QJsonValue
     */
    template<class T> static QJsonValue toJson(const T &t)
    {
        QJsonValue value;
        value << t;
        return value;
    }

    /**
     * @brief fromJson makes type T instance from QJsonValue if possible.
     *        Type parameter `T` should have the function below:
     *        QSharedPointer<T> operator << (QSharedPointer<T> &left, const QJsonValue &right);
     */
    template<class T> static QSharedPointer<T> fromJson(const QJsonValue &json)
    {
        QSharedPointer<T> t;
        json >> t;
        return t;
    }
};

}

#endif // JSONSERIALIZER_H
