/* WorldFrameRepositoryTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMEREPOSITORYTEST_H
#define WORLDFRAMEREPOSITORYTEST_H

#include <QTest>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "corpus/PhonemeKey.h"
#include "corpus/WaveformFrameInfo.h"
#include "corpus/WaveformFrameInfoList.h"
#include "synthesis/world/WorldFrameRepository.h"

#include "AutoTest.h"

using namespace ::testing;

namespace stand
{

class MockPhonemeRepository : public ResourceRepository<PhonemeKey, WaveformFrameInfoList>
{
public:
    MOCK_CONST_METHOD1_T(find, const QSharedPointer<WaveformFrameInfoList>(const PhonemeKey &key));
    MOCK_CONST_METHOD1_T(contains, bool(const PhonemeKey &key));
    MOCK_METHOD2_T(add, bool(const PhonemeKey &key, QSharedPointer<WaveformFrameInfoList> value));
    MOCK_METHOD1_T(remove, void(const PhonemeKey &key));
};

class MockWaveformRepository : public ResourceRepository<QString, WorldWaveform>
{
public:
    MOCK_CONST_METHOD1_T(find, const QSharedPointer<WorldWaveform>(const QString &key));
    MOCK_CONST_METHOD1_T(contains, bool(const QString &key));
    MOCK_METHOD2_T(add, bool(const QString &key, QSharedPointer<WorldWaveform> value));
    MOCK_METHOD1_T(remove, void(const QString &key));
};

class MockFrameAnalyzer : public WorldFrameAnalyzer
{
public:
    MOCK_METHOD3_T(analyze, QSharedPointer<WorldFrame>(const PhonemeKey &key, const QList<WaveformFrameInfo> &infos, const QList<QSharedPointer<WorldWaveform> > &waveforms));
};

class WorldFrameRepositoryTest : public QObject
{
    Q_OBJECT
private slots:
    void find_should_properly_give_data_from_repositories_into_analyzer()
    {
        WaveformFrameInfo e("this_should_be_a_filename_given_to_waveform_repository", 0.7, 0.0);
        QList<WaveformFrameInfo> pieces;
        pieces.append(e);
        pieces.append(e);
        QSharedPointer<WaveformFrameInfoList> waveformFrameInfos = QSharedPointer<WaveformFrameInfoList>(new WaveformFrameInfoList(pieces));
        QSharedPointer<WorldWaveform> waveform(new WorldWaveform());
        QList<QSharedPointer<WorldWaveform> > waveforms;
        waveforms.append(waveform);
        waveforms.append(waveform);
        auto phonemeRepository = QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> >(new MockPhonemeRepository);
        auto waveformRepository = QSharedPointer<ResourceRepository<QString, WorldWaveform> >(new MockWaveformRepository);
        auto frameAnalyzer = QSharedPointer<WorldFrameAnalyzer>(new MockFrameAnalyzer);
        auto frame = QSharedPointer<WorldFrame>(new WorldFrame(16, 256, 200.0));
        PhonemeKey key("hoge", 1.0, 0, 0, 0);

        EXPECT_CALL(*(MockPhonemeRepository *)(phonemeRepository.data()), find(key))
            .Times(1)
            .WillOnce(Return(waveformFrameInfos));
        EXPECT_CALL(*(MockPhonemeRepository *)(phonemeRepository.data()), contains(key))
            .Times(1)
            .WillOnce(Return(true));
        EXPECT_CALL(*(MockWaveformRepository *)(waveformRepository.data()), find(e.filename))
            .Times(2)
            .WillOnce(Return(waveform))
            .WillOnce(Return(waveform));
        EXPECT_CALL(*(MockFrameAnalyzer *)(frameAnalyzer.data()), analyze(key, pieces, waveforms))
            .Times(1)
            .WillOnce(Return(frame));

        WorldFrameRepository repository(phonemeRepository, waveformRepository, frameAnalyzer);
        auto actual = repository.find(key);
        QCOMPARE(actual.data(), frame.data());
    }
};

}

DECLARE_TEST(stand::WorldFrameRepositoryTest)

#endif // WORLDFRAMEREPOSITORYTEST_H
