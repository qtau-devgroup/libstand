/* WaveformFrameInfo.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WAVEFORMFRAMEINFO_H
#define WAVEFORMFRAMEINFO_H

#include <QString>

namespace stand
{

/**
 * @brief The WaveformFrame class is a single frame of vocal waveform.
 *        This class picks up one specified time position of waveform.
 *        Note that operator == is implemented for unit-testing.
 *        == returns true only if all parameters are exactly the same.
 * @author Hal@shurabaP
 */
class WaveformFrameInfo
{
public:
    WaveformFrameInfo(const QString &filename, double msPosition, double amplify);
    WaveformFrameInfo(const WaveformFrameInfo &other);
    WaveformFrameInfo &operator =(const WaveformFrameInfo &other);
    bool operator ==(const WaveformFrameInfo &other) const;

    QString filename;
    double msPosition;
    double amplify;
};

}

#endif // WAVEFORMFRAMEINFO_H
