/* Signal.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef SYNTHESIS_SIGANAL_H
#define SYNTHESIS_SIGANAL_H

#include <QFileInfo>
#include <QVector>

namespace stand
{

/**
 * @brief The Siganal class represents a signal that means an array of waveform with its sampling frequency.
 * @author Hal@shurabaP
 */
class Signal : public QVector<float>
{
public:
    /**
     * @brief Signal creates an empty signal.
     * @param samples
     * @param samplingFrequency
     */
    explicit Signal(int samples = 0, int samplingFrequency = 44100);

    /**
     * @brief Signal is a copy constructor.
     * @param other will be copied to this instance.
     */
    Signal(const Signal &other);

    virtual ~Signal(){ }

    int samplingFrequency() const;
    void setSamplingFrequency(int fs);
private:
    int fs;
};

}

#endif // SYNTHESIS_SIGANAL_H
