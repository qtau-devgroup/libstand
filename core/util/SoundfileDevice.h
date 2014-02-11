/* SoundfileDevice.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef SOUNDFILEDEVICE_H
#define SOUNDFILEDEVICE_H

#include <QSharedPointer>
#include <sndfile.hh>

#include "dsp/Signal.h"

namespace stand
{

/**
 * @brief The SoundfileDevice class is a wrapper to read soundfile from QIODevice.
 * @author Hal@shurabaP
 */
class SoundfileDevice
{
public:
    /**
     * @brief read signals from device. libsndfile specify the format of tha data from device.
     * @param device to read signals.
     * @return signals.
     */
    static QList<Signal> read(QSharedPointer<QIODevice> device);

    /**
     * @brief write signals into device.
     * @param sounds to write.
     * @param format of the sounds. Use a format in libsndfile.
     * @param device to write in.
     * @return if write succeeds.
     */
    static bool write(const QList<Signal> &sounds, int format, QSharedPointer<QIODevice> device);
};

}

#endif // SOUNDFILEDEVICE_H
