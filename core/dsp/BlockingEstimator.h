/* BlockingEstimator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef BLOCKINGESTIMATOR_H
#define BLOCKINGESTIMATOR_H

#include "dsp/Contour.h"

namespace stand
{

class Signal;

template <class T> class BlockingEstimator
{
public:
    virtual ~BlockingEstimator(){ }

    virtual Contour<T> estimate(const Signal &signal, double msFramePeriod) = 0;
};

}

#endif // BLOCKINGESTIMATOR_H
