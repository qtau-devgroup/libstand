/* WaveFileSignalFactory.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QList>
#include "util/SoundfileDevice.h"

#include "WaveFileSignalFactory.h"

using namespace stand;

Signal WaveFileSignalFactory::create(const QString &key)
{
    QSharedPointer<QIODevice> file = QSharedPointer<QFile>(new QFile(key));
    QList<Signal> sounds = SoundfileDevice().read(file);
    if(sounds.empty())
    {
        return Signal();
    }
    return sounds[0];
}
