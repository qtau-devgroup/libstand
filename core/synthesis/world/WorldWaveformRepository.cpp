/* WorldWaveformRepository.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "WorldWaveformRepository.h"

using namespace stand;

WorldWaveformRepository::WorldWaveformRepository(QSharedPointer<ResourceFactory<QString, QSharedPointer<WorldWaveform> > > factory) :
    ResourceRepository<QString, WorldWaveform>::ResourceRepository(factory)
{
}

const QSharedPointer<WorldWaveform> WorldWaveformRepository::find(const QString &key) const
{
    if(!contains(key))
    {
        return QSharedPointer<WorldWaveform>();
    }
    return dictionary.find(key).value();
}

bool WorldWaveformRepository::contains(const QString &key) const
{
    return dictionary.contains(key);
}

bool WorldWaveformRepository::add(const QString &key, QSharedPointer<WorldWaveform> value)
{
    // duplicated key is no good.
    if(!contains(key))
    {
        return false;
    }
    dictionary.insert(key, value);
    return true;
}

void WorldWaveformRepository::remove(const QString &key)
{
    if(!contains(key))
    {
        return;
    }
    dictionary.remove(key);
}
