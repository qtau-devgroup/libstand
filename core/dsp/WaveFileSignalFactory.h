/* WaveFileSignalFactory.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WAVEFILESIGNALFACTORY_H
#define WAVEFILESIGNALFACTORY_H

#include "dsp/Signal.h"
#include "util/ResourceRepository.h"

namespace stand
{

class WaveFileSignalFactory : public ResourceFactory<QString, Signal>
{
public:
    virtual ~WaveFileSignalFactory(){ }
    virtual Signal create(const QString &key);
};

}

#endif // WAVEFILESIGNALFACTORY_H
