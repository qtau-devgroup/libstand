/* ResourceRepository.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "ResourceRepository.h"

using namespace stand;

template <class Key, class T> bool ResourceRepository<Key, T>::add(const Key &key)
{
    if(factory.isNull())
    {
        return false;
    }
    // If not duplicated key, add the created item.
    if(!contains(key))
    {
        return add(key, factory->create(key));
    }
    return false;
}
