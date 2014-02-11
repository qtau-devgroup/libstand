/* PlatinumPeakEstimator.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QPair>
#include <QtMath>
#include "Signal.h"

#include "PlatinumPeakEstimator.h"

using namespace stand;

Contour<qint32> PlatinumPeakEstimator::estimate(const Signal &signal, double msFramePeriod)
{
    QList<QPair<int, int> > analyzeSection = sections(f0);

    QList<int> pulseLocations;
    foreach(const auto &values, analyzeSection)
    {
        pulseLocations += pulseLocationsInOneSection(signal, f0, values.first, values.second, f0.msFramePeriod(), defaultF0);
    }

    if(pulseLocations.empty())
    {
        pulseLocations.append(0);
    }

    int length = (signal.size() / (double)signal.samplingFrequency()) / msFramePeriod;

    return Contour<qint32>(nearestPeaks(signal, pulseLocations, length, msFramePeriod), msFramePeriod);
}

QList<QPair<int, int> > PlatinumPeakEstimator::sections(const Contour<float> &f0)
{
    QList<QPair<int, int> > sections;
    int start = 0;
    for(int i = 1; i < f0.size(); i++)
    {
        // unvoiced section ends.
        if(f0[i] != 0.0 && f0[i - 1] == 0.0)
        {
            sections.append(QPair<int, int>(start, i));
            start = i;
        }
        // voiced section ends.
        if(f0[i] == 0.0 && f0[i -1] != 0.0)
        {
            sections.append(QPair<int, int>(start, i));
            start = i;
        }
    }
    sections.append(QPair<int, int>(start, f0.size() - 1));
    return sections;
}

QList<qint32> PlatinumPeakEstimator::pulseLocationsInOneSection(const Signal &signal, const Contour<float> &f0, int start, int end, double f0FramePeriod, double defaultF0)
{
    const double twoPi = M_PI * 2;
    int startIndex = signal.samplingFrequency() * f0FramePeriod * start / 1000.0;
    int endIndex = signal.samplingFrequency() * f0FramePeriod * end / 1000.0;
    QList<qint32> result;
    result.reserve(endIndex - startIndex);
    double totalPhase = 0.0;
    for(int i = startIndex; i < endIndex; i++)
    {
        double ms = startIndex / (double)signal.samplingFrequency() * 1000.0;
        double freq = f0.at(ms);
        double phaseDiff = (freq == 0.0 ? defaultF0 : freq) * twoPi / signal.samplingFrequency();
        if(fabs(fmod(totalPhase, twoPi) - fmod(totalPhase + phaseDiff, twoPi)) > twoPi)
        {
            result.append((qint32)i);
        }
        totalPhase += phaseDiff;
    }
    return result;
}

QList<qint32> PlatinumPeakEstimator::nearestPeaks(const Signal & signal, const QList<qint32> &pulseLocations, int length, double msFramePeriod)
{
    QList<qint32> peaks;
    peaks.reserve(length);

    int begin = 0;
    for(int i = 0; i < length; i++)
    {
        double index = i * msFramePeriod * signal.samplingFrequency() / 1000.0;
        double minimum = fabs(pulseLocations[begin] - index);
        int nearestPeakIndex = begin;
        for(int j = begin; j < pulseLocations.size(); j++)
        {
            double diff = fabs(pulseLocations[j] - index);
            if(diff < minimum)
            {
                nearestPeakIndex = j;
                minimum = diff;
            }
        }
        peaks.append(nearestPeakIndex);
    }
    return peaks;
}
