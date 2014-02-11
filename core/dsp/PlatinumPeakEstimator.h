/* PlatinumPeakEstimator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef PLATINUMPEAKESTIMATOR_H
#define PLATINUMPEAKESTIMATOR_H

#include <QtGlobal>
#include "dsp/BlockingEstimator.h"

namespace stand
{

/**
 * @brief The PlatinumPeakEstimator class peak picker for platinum.
 * @author Hal@shurabaP
 */
class PlatinumPeakEstimator : public BlockingEstimator<qint32>
{
public:
    PlatinumPeakEstimator(Contour<float> f0, double defaultF0) :
        f0(f0), defaultF0(defaultF0) { }

    virtual ~PlatinumPeakEstimator(){ }

    virtual Contour<qint32> estimate(const Signal &signal, double msFramePeriod);
private:
    Contour<float> f0;
    double defaultF0;
private:
    static QList<QPair<int, int> > sections(const Contour<float> &f0);
    static QList<qint32> pulseLocationsInOneSection(const Signal &signal, const Contour<float> &f0, int start, int end, double f0FramePeriod, double defaultF0);
    static QList<qint32> nearestPeaks(const stand::Signal &signal, const QList<qint32> &pulseLocations, int length, double msFramePeriod);
};

}

#endif // PLATINUMPEAKESTIMATOR_H
