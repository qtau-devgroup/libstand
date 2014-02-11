/* WorldFrameSynthesizer.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMESYNTHESIZER_H
#define WORLDFRAMESYNTHESIZER_H

#include "synthesis/FrameSynthesizer.h"
#include "synthesis/world/WorldFrame.h"
#include "util/ResourceRepository.h"

namespace stand
{

/**
 * @brief The WorldFrameSynthesizer class is an implementation of FrameSynthesizer.
 * @author Hal@shurabaP
 */
class WorldFrameSynthesizer : public FrameSynthesizer<WorldFrame>
{
public:
    explicit WorldFrameSynthesizer(int samplingFrequency) :
        FrameSynthesizer<WorldFrame>(samplingFrequency){ }
    virtual ~WorldFrameSynthesizer(){ }

    /**
     * @brief synthesize synthesizes a signal from WorldFrame with WORLD.
     * @param dst is a buffer to add signal.
     * @param src is a source WORLD frame.
     * @param ms is a time position for adding signal.
     * @return instant frequency.
     */
    double synthesize(Signal &dst, const QSharedPointer<WorldFrame> &src, double ms);
};

}

#endif // WORLDFRAMESYNTHESIZER_H
