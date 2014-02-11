/* WorldFrame.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "dsp/helpers/DoDelete.h"

#include "WorldFrame.h"

using namespace stand;

WorldFrame::WorldFrame(int fftLength, int samplingFrequency, double f0) :
    spectrum(new double[fftLength], helper::DoDelete<double>),
    residual(new double[fftLength], helper::DoDelete<double>),
    fftLength(fftLength), samplingFrequency(samplingFrequency), f0(f0)
{
}

WorldFrame::WorldFrame(const WorldFrame &other) :
    WorldFrame(other.fftLength, other.samplingFrequency, other.f0)
{
}

WorldFrame &WorldFrame::operator =(const WorldFrame &other)
{
    this->spectrum = other.spectrum;
    this->residual = other.residual;
    this->fftLength = other.fftLength;
    this->samplingFrequency = other.samplingFrequency;
    this->f0 = other.f0;
    return (*this);
}

WorldFrame::~WorldFrame()
{
}

void WorldFrame::clear()
{
    for(int i = 0; i < fftLength; i++)
    {
        spectrum.data()[i] = 1.0;
    }
    for(int i = 0; i < fftLength; i++)
    {
        residual.data()[i] = 0.0;
    }
}
