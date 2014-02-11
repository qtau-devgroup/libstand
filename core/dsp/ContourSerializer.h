/* ContourSerializer.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef CONTOURSERIALIZER_H
#define CONTOURSERIALIZER_H

#include <QFileInfo>
#include <QIODevice>
#include <QSharedPointer>

#include "dsp/Contour.h"

namespace stand
{

/**
 * The ContourSerializer class persists Contour.
 * @tparam T should be the sub class of Contour.
 * @author Hal@shurabaP
 */
template <class T> class ContourSerializer
{
public:
    const static QString Identifier;
public:
    virtual ~ContourSerializer(){ }

    virtual Contour<T> read(QSharedPointer<QIODevice> device) const;

    virtual bool write(QSharedPointer<QIODevice> device, const Contour<T> &target) const;
};

}

#endif // CONTOURSERIALIZER_H
