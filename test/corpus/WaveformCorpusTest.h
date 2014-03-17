/* WaveformCorpusTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef WAVEFORMCORPUSTEST_H
#define WAVEFORMCORPUSTEST_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <QTest>

#include "corpus/NotePhonemeMapper.h"
#include "corpus/PhonemeSelector.h"
#include "corpus/WaveformCorpus.h"
#include "helper/MockResourceRepository.h"

#include "AutoTest.h"

using namespace ::testing;

namespace stand
{

class MockNotePhonemeMapper : public NotePhonemeMapper
{
public:
    MOCK_CONST_METHOD2_T(find, NotePhonemeMappingList &(int note, int velocity));
    MOCK_METHOD1_T(subscript, QList<NotePhonemeMappingList> &(int index));

    virtual QList<NotePhonemeMappingList> &operator[](int index)
    {
        return subscript(index);
    }
};

class MockPhonemeSelector : public PhonemeSelector
{
public:
    MOCK_CONST_METHOD2_T(select, QSharedPointer<WaveformFrameInfoList> (const NotePhonemeMappingList &items, const QList<QSharedPointer<Phoneme> > &phonemes));
};

class WaveformCorpusTest : public QObject
{
    Q_OBJECT
private slots:
    void find_should_return_the_proper_value_from_all_repositories()
    {
        MockNotePhonemeMapper *mockedPhonemeMapper = new MockNotePhonemeMapper;
        MockResourceRepository<QString, Phoneme> *mockedPhonemeRepository1 = new MockResourceRepository<QString, Phoneme>;
        MockResourceRepository<QString, Phoneme> *mockedPhonemeRepository2 = new MockResourceRepository<QString, Phoneme>;
        QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > repositories;
        repositories.insert(QString("1"), QSharedPointer<ResourceRepository<QString, Phoneme> >(mockedPhonemeRepository1));
        repositories.insert(QString("2"), QSharedPointer<ResourceRepository<QString, Phoneme> >(mockedPhonemeRepository2));

        MockPhonemeSelector *selector = new MockPhonemeSelector;

        NotePhonemeMappingList items;
        NotePhonemeMappingItem item1("1", 0.0, 1.0);
        NotePhonemeMappingItem item2("2", 1.0, 0.0);
        items.append(item1);
        items.append(item2);

        Phoneme *phoneme1 = new Phoneme("filename1", 0, 1, 2, 3, 4);
        Phoneme *phoneme2 = new Phoneme("filename2", 4, 3, 2, 1, 0);
        QList<QSharedPointer<Phoneme> > phonemes;
        phonemes.append(QSharedPointer<Phoneme>(phoneme1));
        phonemes.append(QSharedPointer<Phoneme>(phoneme2));

        QSharedPointer<WaveformFrameInfoList> expected(new WaveformFrameInfoList);

        int velocity = 32;
        int noteNumber = 44;
        PhonemeKey key("pronounce", 1.0, 0.0, velocity, noteNumber);
        EXPECT_CALL(*mockedPhonemeMapper, find(noteNumber, velocity))
                .WillOnce(ReturnRef(items))
                .WillOnce(ReturnRef(items));

        EXPECT_CALL(*mockedPhonemeRepository1, find(key.pronounce))
                .WillOnce(Return(phonemes[0]));

        EXPECT_CALL(*mockedPhonemeRepository2, find(key.pronounce))
                .WillOnce(Return(phonemes[1]));

        EXPECT_CALL(*selector, select(items, phonemes))
                .WillOnce(Return(expected));

        WaveformCorpus corpus(
                    CorpusMeta(QString("test"), QString(), QString(), QString(), QString()),
                    QSharedPointer<NotePhonemeMapper>(mockedPhonemeMapper),
                    repositories,
                    QSharedPointer<PhonemeSelector>(selector));
        QCOMPARE(corpus.find(key).data(), expected.data());
    }
    void find_should_null_one_of_repository_id_not_found()
    {
        MockNotePhonemeMapper *mockedPhonemeMapper = new MockNotePhonemeMapper;
        MockResourceRepository<QString, Phoneme> *mockedPhonemeRepository1 = new MockResourceRepository<QString, Phoneme>;
        QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > repositories;
        repositories.insert(QString("1"), QSharedPointer<ResourceRepository<QString, Phoneme> >(mockedPhonemeRepository1));

        MockPhonemeSelector *selector = new MockPhonemeSelector;

        NotePhonemeMappingList items;
        NotePhonemeMappingItem item1("1", 0.0, 1.0);
        NotePhonemeMappingItem item2("2", 1.0, 0.0);
        items.append(item1);
        items.append(item2);

        QSharedPointer<WaveformFrameInfoList> expected(new WaveformFrameInfoList);

        int velocity = 32;
        int noteNumber = 44;
        PhonemeKey key("pronounce", 1.0, 0.0, velocity, noteNumber);
        EXPECT_CALL(*mockedPhonemeMapper, find(noteNumber, velocity))
                .WillOnce(ReturnRef(items));

        EXPECT_CALL(*mockedPhonemeRepository1, find(_))
                .Times(0);

        EXPECT_CALL(*selector, select(_, _))
                .Times(0);

        WaveformCorpus corpus(
                    CorpusMeta(QString("test"), QString(), QString(), QString(), QString()),
                    QSharedPointer<NotePhonemeMapper>(mockedPhonemeMapper),
                    repositories,
                    QSharedPointer<PhonemeSelector>(selector));
        QCOMPARE(corpus.find(key).isNull(), true);
    }
};

}

DECLARE_TEST(stand::WaveformCorpusTest)

#endif // WAVEFORMCORPUSTEST_H
