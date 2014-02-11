/* Signal.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "dsp/Signal.h"

using namespace stand;

Signal::Signal(int samples, int samplingFrequency) :
    QVector(), fs(samplingFrequency)
{
    this->resize(samples);
}

Signal::Signal(const Signal &other) :
    QVector(other), fs(other.samplingFrequency())
{
}

int Signal::samplingFrequency() const
{
    return fs;
}

void Signal::setSamplingFrequency(int fs)
{
    this->fs = fs;
}
