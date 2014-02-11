/* F0Estimator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef F0ESTIMATOR_H
#define F0ESTIMATOR_H

#include "dsp/BlockingEstimator.h"
#include "dsp/Contour.h"

namespace stand
{

class Signal;

/**
 * @brief The F0Estimator class is an interface class for F0 estimator.
 */
class F0Estimator : public BlockingEstimator<float>
{
public:
    virtual ~F0Estimator(){ }

    /**
     * @brief estimate estimates F0 countour.
     * @param wave is a signal to estimate F0.
     * @param msFramePeriod is a period length of estimation.
     * @return F0 contour.
     */
    virtual Contour<float> estimate(const Signal &signal, double msFramePeriod) = 0;
};

}

#endif // F0ESTIMATOR_H
