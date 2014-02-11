/* WorldKeyListFrameProvider.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDKEYLISTFRAMEPROVIDER_H
#define WORLDKEYLISTFRAMEPROVIDER_H

#include "corpus/PhonemeKey.h"
#include "synthesis/FrameProvider.h"
#include "synthesis/world/WorldFrame.h"
#include "util/ResourceRepository.h"

namespace stand
{

class WorldKeyListFrameProvider : public FrameProvider<WorldFrame>
{
public:
    WorldKeyListFrameProvider(
        QList<PhonemeKey> keys,
        double msFramePeriod,
        QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository
    ) : keys(keys), msFramePeriod(msFramePeriod), frameRepository(frameRepository){ }

    /**
     * @brief at should return the T data at ms[msec].
     */
    virtual const QSharedPointer<WorldFrame> at(double ms) const;

    /**
     * @brief msLength returns data length.
     * @return data length[msec].
     */
    virtual double msLength() const;

private:
    QList<PhonemeKey> keys;
    double msFramePeriod;
    QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository;
};

}

#endif // WORLDKEYLISTFRAMEPROVIDER_H
