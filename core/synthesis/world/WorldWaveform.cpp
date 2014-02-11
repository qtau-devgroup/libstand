/* WorldWaveform.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "WorldWaveform.h"

using namespace stand;

WorldWaveform::WorldWaveform(const Signal &signal, const Contour<float> &f0Contour, const Contour<int> &peakIndices, double msFramePeriod) :
    signal(signal), f0Contour(f0Contour), peakIndices(peakIndices), msFramePeriod(msFramePeriod)
{
}

WorldWaveform::WorldWaveform(const WorldWaveform &other) :
    WorldWaveform(other.signal, other.f0Contour, other.peakIndices, other.msFramePeriod)
{
}

WorldWaveform &WorldWaveform::operator =(const WorldWaveform &other)
{
    this->signal = other.signal;
    this->f0Contour = other.f0Contour;
    this->peakIndices = other.peakIndices;
    this->msFramePeriod = other.msFramePeriod;
    return (*this);
}
