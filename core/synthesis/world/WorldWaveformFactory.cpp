/* WorldWaveformFactory.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QDir>
#include "dsp/DioF0Estimator.h"
#include "dsp/PlatinumPeakEstimator.h"
#include "WorldWaveformFactory.h"

using namespace stand;

QSharedPointer<WorldWaveform> WorldWaveformFactory::create(const QString &key)
{
    if(signalFactory.isNull())
    {
        return QSharedPointer<WorldWaveform>();
    }
    Signal signal(signalFactory->create(key));
    if(signal.isEmpty())
    {
        return QSharedPointer<WorldWaveform>();
    }
    Contour<float> f0(readOrEstimateF0(signal, key));
    Contour<int> peak(readOrEstimatePeak(signal, key, f0));

    if(f0.empty() || peak.empty())
    {
        return QSharedPointer<WorldWaveform>();
    }
    return QSharedPointer<WorldWaveform>(new WorldWaveform(signal, f0, peak, msFramePeriod));
}

Contour<float> WorldWaveformFactory::readOrEstimateF0(const Signal &signal, const QString &key)
{
    QFileInfo signalPath(key);
    Contour<float> f0;
    QFileInfo f0File(signalPath.absoluteDir().filePath(signalPath.baseName() + F0Extention));
    if(!f0Serializer.isNull())
    {
        QSharedPointer<QFile> file(new QFile(f0File.absoluteFilePath()));
        f0 = f0Serializer->read(file);
    }
    if(f0.empty())
    {
        f0 = DioF0Estimator().estimate(signal, msFramePeriod);
        QSharedPointer<QFile> file(new QFile(f0File.absoluteFilePath()));
        if(!f0Serializer.isNull() && !f0.empty())
        {
            f0Serializer->write(file, f0);
        }
    }
    return f0;
}

Contour<int> WorldWaveformFactory::readOrEstimatePeak(const Signal &signal, const QString &key, const Contour<float> &f0)
{
    QFileInfo signalPath(key);
    Contour<int> peak;
    QFileInfo peakFile(signalPath.absoluteDir().filePath(signalPath.baseName() + PeakExtention));
    if(!peakSerializer.isNull())
    {
        QSharedPointer<QFile> file(new QFile(peakFile.absoluteFilePath()));
        peak = peakSerializer->read(file);
    }
    if(peak.empty())
    {
        peak = PlatinumPeakEstimator(f0, defaultF0).estimate(signal, msFramePeriod);
        QSharedPointer<QFile> file(new QFile(peakFile.absoluteFilePath()));
        if(!peakSerializer.isNull() && !peak.empty())
        {
            peakSerializer->write(file, peak);
        }
    }
    return peak;
}
