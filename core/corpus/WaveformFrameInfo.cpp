/* WaveformFrameInfo.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "WaveformFrameInfo.h"

using namespace stand;

WaveformFrameInfo::WaveformFrameInfo(const QString &filename, double msPosition, double amplify) :
    filename(filename), msPosition(msPosition), amplify(amplify)
{
}

WaveformFrameInfo::WaveformFrameInfo(const WaveformFrameInfo &other) :
    WaveformFrameInfo(other.filename, other.msPosition, other.amplify)
{
}

WaveformFrameInfo &WaveformFrameInfo::operator =(const WaveformFrameInfo &other)
{
    this->filename = other.filename;
    this->msPosition = other.msPosition;
    this->amplify = other.amplify;
    return *this;
}

bool WaveformFrameInfo::operator ==(const WaveformFrameInfo &other) const
{
    return this->filename == other.filename &&
            this->msPosition == other.msPosition &&
            this->amplify == other.amplify;
}
