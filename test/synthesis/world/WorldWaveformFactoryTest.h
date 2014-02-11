/* WorldWaveformFactoryTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDWAVEFORMFACTORYTEST_H
#define WORLDWAVEFORMFACTORYTEST_H

#include <QTest>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "synthesis/world/WorldWaveformFactory.h"

#include "AutoTest.h"

using namespace ::testing;

namespace stand
{

class DummySignalFactory : public ResourceFactory<QString, Signal>
{
public:
    MOCK_METHOD1_T(create, Signal(const QString &key));
};

template<class T> class DummySerializer : public ContourSerializer<T>
{
public:
    MOCK_CONST_METHOD1_T(read, Contour<T>(QSharedPointer<QIODevice> device));
    MOCK_CONST_METHOD2_T(write, bool(QSharedPointer<QIODevice> device, const Contour<T> &target));
};

class WorldWaveformFactoryTest : public QObject
{
    Q_OBJECT
private slots:
    void create_succeeds_when_waveform_factory_successfuly_reads_all_parameters()
    {
        DummySerializer<float> *f0 = new DummySerializer<float>;
        DummySerializer<qint32> *peak = new DummySerializer<qint32>;
        DummySignalFactory *signal = new DummySignalFactory;
        QSharedPointer<ResourceFactory<QString, Signal> > signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(signal);
        QSharedPointer<ContourSerializer<float> > f0Serializer = QSharedPointer<ContourSerializer<float> >(f0);
        QSharedPointer<ContourSerializer<qint32> > peakSerializer = QSharedPointer<ContourSerializer<int> >(peak);
        WorldWaveformFactory sut(1.0, 71.0, signalFactory, f0Serializer, peakSerializer);

        QString fakeKey = "dummy";
        Signal fakeSignal(1024);
        Contour<float> fakeF0; fakeF0.append(1.0f);
        Contour<int> fakePeak; fakePeak.append(1);

        EXPECT_CALL(*signal, create(fakeKey)).Times(1).WillOnce(Return(fakeSignal));
        EXPECT_CALL(*f0, read(_)).Times(1).WillOnce(Return(fakeF0));
        EXPECT_CALL(*peak, read(_)).Times(1).WillOnce(Return(fakePeak));

        auto result = sut.create(fakeKey);
        QCOMPARE(result->f0Contour, fakeF0);
        QCOMPARE(result->peakIndices, fakePeak);
        QCOMPARE(result->signal, fakeSignal);
    }

    void create_succeeds_and_writes_f0_and_peak_files_when_waveform_found_but_f0_and_peak_not_found()
    {
        DummySerializer<float> *f0 = new DummySerializer<float>;
        DummySerializer<qint32> *peak = new DummySerializer<qint32>;
        DummySignalFactory *signal = new DummySignalFactory;
        QSharedPointer<ResourceFactory<QString, Signal> > signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(signal);
        QSharedPointer<ContourSerializer<float> > f0Serializer = QSharedPointer<ContourSerializer<float> >(f0);
        QSharedPointer<ContourSerializer<qint32> > peakSerializer = QSharedPointer<ContourSerializer<int> >(peak);
        WorldWaveformFactory sut(1.0, 71.0, signalFactory, f0Serializer, peakSerializer);
        QString fakeKey = "dummy";
        Signal fakeSignal(44100);
        for(int i = 0; i < fakeSignal.size(); i++)
        {
            fakeSignal[i] = 0.0f;
        }
        Contour<float> fakeF0; fakeF0.append(1.0f);
        Contour<int> fakePeak; fakePeak.append(1);

        EXPECT_CALL(*signal, create(fakeKey)).Times(1).WillOnce(Return(fakeSignal));
        EXPECT_CALL(*f0, read(_)).Times(1).WillOnce(Return(Contour<float>()));
        EXPECT_CALL(*peak, read(_)).Times(1).WillOnce(Return(Contour<int>()));
        EXPECT_CALL(*f0, write(_, _)).Times(1).WillOnce(Return(true));
        EXPECT_CALL(*peak, write(_, _)).Times(1).WillOnce(Return(true));

        auto result = sut.create(fakeKey);
        QCOMPARE(result->f0Contour.empty(), false);
        QCOMPARE(result->peakIndices.empty(), false);
        QCOMPARE(result->signal, fakeSignal);
    }
};

}

DECLARE_TEST(stand::WorldWaveformFactoryTest)

#endif // WORLDWAVEFORMFACTORYTEST_H
