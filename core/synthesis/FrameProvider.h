/* FrameProvider.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include <QSharedPointer>

namespace stand
{

/**
 * @brief The FrameProvider class is a data provider for FrameSynthesizer.
 * @tparam T is a data type.
 * @author Hal@shurabaP
 */
template <class T> class FrameProvider
{
public:
    virtual ~FrameProvider(){ }

    /**
     * @brief at should return the T data at ms[msec].
     */
    virtual const QSharedPointer<T> at(double ms) const = 0;

    /**
     * @brief msLength returns data length.
     * @return data length[msec].
     */
    virtual double msLength() const = 0;
};


}

#endif // FRAMEPROVIDER_H
