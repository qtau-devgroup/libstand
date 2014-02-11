/* Contour.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef CONTOUR_H
#define CONTOUR_H

#include <QList>

namespace stand
{

/**
 * @brief The Contour class represents data of time direction.
 *        Contour is a thin wrapper of QList.
 *        Contour just has `msFramePeriod` that means time length of a single index.
 * @tpram T is a data type.
 * @author Hal@shurabaP
 */
template <class T> class Contour : public QList<T>
{
public:
    Contour() : Contour(0, 0.0){ }
    Contour(int size, double msFramePeriod) :
        framePeriod(msFramePeriod)
    {
        this->reserve(size);
    }

    Contour(const QList<T> &data, double msFramePeriod) :
        QList<T>(data), framePeriod(msFramePeriod)
    {
    }

    Contour(const Contour &other) :
        QList<T>(other), framePeriod(other.msFramePeriod())
    {
    }

    virtual ~Contour(){}

    double msFramePeriod() const
    {
        return framePeriod;
    }

    void setMsFramePeriod(double msFramePeriod)
    {
        framePeriod = msFramePeriod;
    }

    double msLength() const
    {
        return framePeriod * this->size();
    }

    /**
     * @brief at returns data at ms[msec]. This method uses nearest-neighborhood.
     * @param ms is a time position of milli seconds.
     * @return data nearest the time position.
     */
    const T &at(double ms) const
    {
        int index = ms / framePeriod;
        index = qMax(0, qMin(index, this->size()));
        return at(index);
    }

    const T &at(int index) const
    {
        return QList<T>::at(index);
    }
private:
    double framePeriod;
};

}

#endif // CONTOUR_H
