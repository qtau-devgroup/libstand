/* AutoTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef AUTOTEST_H
#define AUTOTEST_H

#include <QTest>
#include <QHash>
#include <QString>
#include <QSharedPointer>

namespace stand
{

namespace QAutoTest
{
QHash<QString, QObject *> &tests();

int run(int argc, char *argv[]);
}

template <class T> class Test
{
public:
    QSharedPointer<T> test;
    Test(const QString &name) : test(new T)
    {
        if(!QAutoTest::tests().contains(name))
        {
            QAutoTest::tests()[name] = test.data();
        }
    }
};

}

#define DECLARE_TEST(className) static stand::Test<className> t(#className);

#endif // AUTOTEST_H
