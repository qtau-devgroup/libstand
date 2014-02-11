/* AutoTest.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "AutoTest.h"

using namespace stand;

QHash<QString, QObject *> &QAutoTest::tests()
{
    static QHash<QString, QObject *> t;
    return t;
}

int QAutoTest::run(int argc, char *argv[])
{
    int ret = 0;
    QList<QString> failureTests;
    foreach(QObject* test, tests().values())
    {
        int result =  QTest::qExec(test, argc, argv);
        if(result)
        {
            failureTests.append(tests().key(test));
        }
        ret |= result;
    }
    if(ret == 0)
    {
        printf("[success] All test succeeded!\n");
    }
    else
    {
        printf("[error] %d test(s) failed.\n", failureTests.size());
        foreach(const QString &testName, failureTests)
        {
            printf("[error]  Test failed in: %s\n", testName.toLocal8Bit().data());
        }
    }
    return ret;
}
