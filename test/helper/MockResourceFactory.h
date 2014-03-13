/* MockResourceFactory.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef MOCKRESOURCEFACTORY_H
#define MOCKRESOURCEFACTORY_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "util/ResourceRepository.h"

namespace stand
{

template <class Key, class T> class MockResourceFactory : public ResourceFactory<Key, T>
{
public:
    MOCK_METHOD1_T(create, T (const Key &key));
};

}

#endif // MOCKRESOURCEFACTORY_H
