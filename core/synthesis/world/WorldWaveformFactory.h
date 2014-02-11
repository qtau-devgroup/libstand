/* WorldWaveformFactory.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDWAVEFORMFACTORY_H
#define WORLDWAVEFORMFACTORY_H

#include<QList>

#include "dsp/BlockingEstimator.h"
#include "dsp/Contour.h"
#include "dsp/ContourSerializer.h"
#include "dsp/F0Estimator.h"
#include "dsp/WaveFileSignalFactory.h"
#include "util/ResourceRepository.h"
#include "synthesis/world/WorldWaveform.h"

namespace stand
{

/**
 * @brief The WorldWaveformFactory class is a factory class for WorldWaveform.
 *        This class tries to read WorldWaveform from files.
 *        If only waveform found, WorldWaveformFactory calculates f0 contour by f0Estimator and peak indices by peakEstimator.
 *        If either of estimators is NULL, WorldWaveformFactory::create return NULL.
 * @author Hal@shurabaP
 */
class WorldWaveformFactory : public ResourceFactory<QString, QSharedPointer<WorldWaveform> >
{
public:
    const QString F0Extention = "standf0";
    const QString PeakExtention = "standpeak";
public:
    /**
     * @brief WorldWaveformFactory is a basic constructor.
     * @param signalFactory is a factory class of Signal.
     * @param f0Estimator is estimator for f0.
     * @param peakEstimator is estimator for peaks.
     */
    WorldWaveformFactory(
        double msFramePeriod,
        double defaultF0,
        QSharedPointer<ResourceFactory<QString, Signal> > signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(new WaveFileSignalFactory),
        QSharedPointer<ContourSerializer<float> > f0Serializer = QSharedPointer<ContourSerializer<float> >(new ContourSerializer<float>),
        QSharedPointer<ContourSerializer<qint32> > peakSerializer = QSharedPointer<ContourSerializer<int> >(new ContourSerializer<int>)
    ) : msFramePeriod(msFramePeriod),
        defaultF0(defaultF0),
        signalFactory(signalFactory),
        f0Serializer(f0Serializer),
        peakSerializer(peakSerializer) { }

    virtual ~WorldWaveformFactory(){ }

    /**
     * @brief create creates WorldWaveform instance from key that is a filepath.
     * @param key is a filepath.
     * @return WorldWaveform if this class could find WorldWaveform file or calculate f0 and peaks from wave file.
     *         NULL if this class could not find Worldwaveform or calculate f0 or peaks.
     */
    virtual QSharedPointer<WorldWaveform> create(const QString &key);

private:
    Contour<float> readOrEstimateF0(const Signal &signal, const QString &key);
    Contour<int> readOrEstimatePeak(const Signal &signal, const QString &key, const Contour<float> &f0);

    double msFramePeriod;
    double defaultF0;
    QSharedPointer<ResourceFactory<QString, Signal> > signalFactory;
    QSharedPointer<ContourSerializer<float> > f0Serializer;
    QSharedPointer<ContourSerializer<qint32> > peakSerializer;
};

}

#endif // WORLDWAVEFORMFACTORY_H
