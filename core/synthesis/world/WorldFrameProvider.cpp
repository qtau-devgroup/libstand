#include "WorldFrameProvider.h"

using namespace stand;

const QSharedPointer<WorldFrame> WorldFrameProvider::at(double ms) const
{
    int index = ms / msFramePeriod;
    if(index < 0 || keys.size() <= index)
    {
        return QSharedPointer<WorldFrame>();
    }

    return frameRepository->find(keys[index]);
}

double WorldFrameProvider::msLength() const
{
    return msFramePeriod * keys.size();
}
