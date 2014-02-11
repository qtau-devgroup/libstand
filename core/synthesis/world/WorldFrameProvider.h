/* WorldFrameProvider.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMEPROVIDER_H
#define WORLDFRAMEPROVIDER_H

#include "corpus/PhonemeKey.h"
#include "util/ResourceRepository.h"
#include "synthesis/FrameProvider.h"
#include "synthesis/world/WorldFrame.h"

namespace stand
{

/**
 * @brief The WorldFrameProvider class provides WorldFrame at the specified time.
 * @author Hal@shurabaP
 */
class WorldFrameProvider : public FrameProvider<WorldFrame>
{
public:
    WorldFrameProvider(
        const QList<PhonemeKey> &keys,
        double msFramePeriod,
        QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository
    ) : keys(keys), msFramePeriod(msFramePeriod), frameRepository(frameRepository){ }

    virtual ~WorldFrameProvider(){ }

    /**
     * @brief at returns WorldFrame at ms[msec].
     *        WorldFrameProvider uses nearest-neighborhood to choose index of the specified time position.
     */
    virtual const QSharedPointer<WorldFrame> at(double ms) const;

    virtual double msLength() const;
private:
    QList<PhonemeKey> keys;
    double msFramePeriod;
    QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository;
};

}

#endif // WORLDFRAMEPROVIDER_H
