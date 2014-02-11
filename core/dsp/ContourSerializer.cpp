/* ContourSerializer.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QDataStream>

#include "ContourSerializer.h"

using namespace stand;

template <class T> const QString ContourSerializer<T>::Identifier = "Contour";

template <class T> Contour<T> ContourSerializer<T>::read(QSharedPointer<QIODevice> device) const
{
    if(device.isNull() || !device->open(QIODevice::ReadOnly))
    {
        return Contour<T>();
    }
    QDataStream stream(device.data());
    QString header;
    stream >> header;
    if(header != Identifier)
    {
        return Contour<T>();
    }
    double msFramePeriod;
    int size;
    stream >> msFramePeriod >> size;
    if(msFramePeriod <= 0.0 || size <= 0)
    {
        return Contour<T>();
    }
    Contour<T> contour(size, msFramePeriod);
    for(int i = 0; i < size; i++)
    {
        T value;
        stream >> value;
        contour.append(value);
    }
    device->close();
    return contour;
}

template <class T> bool ContourSerializer<T>::write(QSharedPointer<QIODevice> device, const Contour<T> &target) const
{
    if(device.isNull() || !device->open(QIODevice::WriteOnly))
    {
        return false;
    }
    QDataStream stream(device.data());
    stream << Identifier << target.msFramePeriod() << target.size();
    foreach(const T &data, target)
    {
        stream << data;
    }
    device->close();
    return true;
}

template class ContourSerializer<qint32>;
template class ContourSerializer<float>;
