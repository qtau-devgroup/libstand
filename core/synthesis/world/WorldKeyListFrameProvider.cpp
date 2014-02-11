/* WorldKeyListFrameProvider.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "WorldKeyListFrameProvider.h"

using namespace stand;

const QSharedPointer<WorldFrame> WorldKeyListFrameProvider::at(double ms) const
{
    int index = ms / msFramePeriod;
    if(index < 0 || keys.size() <= index)
    {
        return QSharedPointer<WorldFrame>();
    }
    return frameRepository->find(keys[index]);
}

double WorldKeyListFrameProvider::msLength() const
{
    return keys.size() * msFramePeriod;
}
