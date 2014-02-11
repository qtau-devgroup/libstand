/* WorldFrameProviderTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMEPROVIDERTEST_H
#define WORLDFRAMEPROVIDERTEST_H

#include <QTest>

#include "synthesis/world/WorldFrameProvider.h"

#include "AutoTest.h"

namespace stand
{

class DummyWorldFrameRepository : public ResourceRepository<PhonemeKey, WorldFrame>
{
public:
    explicit DummyWorldFrameRepository() : ResourceRepository<PhonemeKey, WorldFrame>(){ }
    virtual ~DummyWorldFrameRepository(){ }

    virtual const QSharedPointer<WorldFrame> find(const PhonemeKey &key) const
    {
        if(key.pronounce == "valid")
        {
            return QSharedPointer<WorldFrame>(new WorldFrame(100, 100, key.amplify));
        }
        return QSharedPointer<WorldFrame>();
    }

    virtual bool contains(const PhonemeKey &key) const
    {
        if(key.pronounce == "valid")
        {
            return true;
        }
        return false;
    }

    virtual bool add(const PhonemeKey &/*key*/, QSharedPointer<WorldFrame> /*value*/){return false;}
    virtual void remove(const PhonemeKey &/*key*/){ }
};

class WorldFrameProviderTest : public QObject
{
    Q_OBJECT
private slots:
    void at_should_return_null_when_no_key_or_no_repository_exists()
    {
        QList<PhonemeKey> keys;
        double msFramePeriod = 1.0;
        QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository(new DummyWorldFrameRepository());
        WorldFrameProvider provider(keys, msFramePeriod, frameRepository);
        QCOMPARE(provider.at(0.0).isNull(), true);
    }
    void at_should_return_null_when_no_repository_element_exists()
    {
        QList<PhonemeKey> keys;
        for(int i = 0; i < 10; i++)
        {
            keys.append(PhonemeKey("a", (double)i, 0.0, 0.0, 0.0));
        }

        double msFramePeriod = 1.0;
        QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository(new DummyWorldFrameRepository());
        WorldFrameProvider provider(keys, msFramePeriod, frameRepository);
        QCOMPARE(provider.at(0.0).isNull(), true);
    }
    void at_should_return_null_when_no_repository_exists()
    {
        QList<PhonemeKey> keys;
        double msFramePeriod = 1.0;
        QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository(new DummyWorldFrameRepository());
        WorldFrameProvider provider(keys, msFramePeriod, frameRepository);
        QCOMPARE(provider.at(0.0).isNull(), true);
    }
    void at_should_succeed()
    {
        QList<PhonemeKey> keys;
        for(int i = 0; i < 10; i++)
        {
            keys.append(PhonemeKey("valid", (double)i, 0.0, 0.0, 0.0));
        }
        double msFramePeriod = 1.0;
        QSharedPointer<ResourceRepository<PhonemeKey, WorldFrame> > frameRepository(new DummyWorldFrameRepository());
        WorldFrameProvider provider(keys, msFramePeriod, frameRepository);
        QCOMPARE(provider.msLength(), keys.size() * msFramePeriod);
        QCOMPARE(provider.at(4.0)->f0, 4.0);
    }
};

}

DECLARE_TEST(stand::WorldFrameProviderTest)

#endif // WORLDFRAMEPROVIDERTEST_H
