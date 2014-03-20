/* SoundfileDevice.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QList>

#include "SoundfileDevice.h"

using namespace stand;

namespace
{
static sf_count_t callbackLength(void *voidDevice)
{
    QIODevice *device = (QIODevice *)voidDevice;
    return device->bytesAvailable();
}

static sf_count_t callbackSeek(sf_count_t offset, int whence, void *voidDevice)
{
    QIODevice *device = (QIODevice *)voidDevice;
    switch(whence)
    {
    case SEEK_CUR:
        device->seek(device->pos() + offset);
        break;
    case SEEK_SET:
        device->seek(offset);
        break;
    case SEEK_END:
        device->seek(offset + callbackLength(voidDevice));
        break;
    }
    return device->pos();
}

static sf_count_t callbackRead(void *ptr, sf_count_t count, void *voidDevice)
{
    QIODevice *device = (QIODevice *)voidDevice;
    return device->read((char *)ptr, count);
}

static sf_count_t callbackWrite(const void *ptr, sf_count_t count, void *voidDevice)
{
    QIODevice *device = (QIODevice *)voidDevice;
    return device->write((const char *)ptr, count);
}

static sf_count_t callbackTell(void *voidDevice)
{
    QIODevice *device = (QIODevice *)voidDevice;
    return device->pos();
}

static SF_VIRTUAL_IO io =
{
    callbackLength,
    callbackSeek,
    callbackRead,
    callbackWrite,
    callbackTell
};

}


QList<Signal> SoundfileDevice::read(QSharedPointer<QIODevice> device)
{
    SF_INFO info{0, 0, 0, 0, 0, 0};
    if(device.isNull() || !device->open(QIODevice::ReadOnly) || !device->seek(0))
    {
        return QList<Signal>();
    }
    SNDFILE *file = sf_open_virtual(&io, SFM_READ, &info, device.data());
    if(!file)
    {
        qDebug("An error happens while opening a sound file : %s", sf_strerror(file));
        return QList<Signal>();
    }
    QList<Signal> sounds;
    for(int i = 0; i < info.channels; i++)
    {
        sounds.append(Signal(info.frames, info.samplerate));
    }

    float data[info.channels * info.frames];
    sf_readf_float(file, data, info.frames);
    sf_close(file);
    device->close();
    for(int frame = 0; frame < info.frames; frame++)
    {
        int indexBase = frame * info.channels;
        for(int channel = 0; channel < info.channels; channel++)
        {
            sounds[channel][frame] = data[indexBase + channel];
        }
    }
    return sounds;
}

bool SoundfileDevice::write(const QList<Signal> &sounds, int format, QSharedPointer<QIODevice> device)
{
    if(device.isNull() || !device->open(QIODevice::WriteOnly))
    {
        return false;
    }
    if(sounds.empty())
    {
        return false;
    }
    sf_count_t frames = sounds[0].size();
    int samplerate = sounds[0].samplingFrequency();
    for(int i = 1; i < sounds.size(); i++)
    {
        frames = qMax((qint64)frames, (qint64)sounds[i].size());
        if(samplerate != sounds[i].samplingFrequency())
        {
            return false;
        }
    }
    if(frames <= 0)
    {
        return false;
    }

    SF_INFO info;
    info.samplerate = samplerate;
    info.format = format;
    info.channels = sounds.size();

    if(sf_format_check(&info) == 0)
    {
        qDebug("Invalid format: %d", format);
        return false;
    }

    SNDFILE *file = sf_open_virtual(&io, SFM_WRITE, &info, device.data());
    if(!file)
    {
        qDebug("An error happens while opening a sound file : %s", sf_strerror(file));
        return false;
    }
    float *data = new float[frames * sounds.size()];
    for(int channel = 0; channel < sounds.size(); channel++)
    {
        int frame;
        for(frame = 0; frame < sounds[channel].size(); frame++)
        {
            data[sounds.size() * frame + channel] = sounds[channel][frame];
        }
        for(; frame < frames; frame++)
        {
            data[sounds.size() * frame + channel] = 0.0f;
        }
    }
    bool result = (frames == sf_writef_float(file, data, frames));

    delete[] data;
    sf_close(file);
    device->close();

    return result;
}
