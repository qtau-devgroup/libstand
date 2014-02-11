/* main.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "AutoTest.h"

using namespace stand;

int main(int argc, char *argv[])
{
    ::testing::GTEST_FLAG(throw_on_failure) = true;
    ::testing::InitGoogleMock(&argc, argv);
    return QAutoTest::run(argc, argv);
}
