/* MockResourceRepository.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef MOCKRESOURCEREPOSITORY_H
#define MOCKRESOURCEREPOSITORY_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "util/ResourceRepository.h"

namespace stand
{

/**
 * @brief MockResourceRepository is a mock class of ResourceRepository.
 * @author Hal@shurabaP
 */
template <class Key, class T> class MockResourceRepository : public ResourceRepository<Key, T>
{
public:
    MOCK_CONST_METHOD1_T(find, const QSharedPointer<T>(const Key &key));
    MOCK_CONST_METHOD1_T(contains, bool(const Key &key));
    MOCK_METHOD2_T(add, bool(const Key &key, QSharedPointer<T> value));
    MOCK_METHOD1_T(remove, void(const Key &key));
};

}

#endif // MOCKRESOURCEREPOSITORY_H
