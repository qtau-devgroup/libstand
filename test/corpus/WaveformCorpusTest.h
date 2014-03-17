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

namespace
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
    MOCK_CONST_METHOD3_T(select, QSharedPointer<WaveformFrameInfoList> (double msPosition, const NotePhonemeMappingList &items, const QList<QSharedPointer<Phoneme> > &phonemes));
};

}

class WaveformCorpusTest : public QObject
{
    Q_OBJECT
private slots:
    void contains_should_return_true_in()
    {
        MockNotePhonemeMapper *notePhonemeMapper = new MockNotePhonemeMapper;
        MockPhonemeSelector *phonemeSelector = new MockPhonemeSelector;
        MockResourceRepository<QString, Phoneme> *phonemeRepository1 = new MockResourceRepository<QString, Phoneme>;
        MockResourceRepository<QString, Phoneme> *phonemeRepository2 = new MockResourceRepository<QString, Phoneme>;
        QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
        phonemeRepositories.insert("1", QSharedPointer<ResourceRepository<QString, Phoneme> >(phonemeRepository1));
        phonemeRepositories.insert("2", QSharedPointer<ResourceRepository<QString, Phoneme> >(phonemeRepository2));
        NotePhonemeMappingList items;
        items.append(NotePhonemeMappingItem("1", 0.5));
        items.append(NotePhonemeMappingItem("2", 0.5));

        PhonemeKey key("test", 1.0, 0.0, 32, 64);
        EXPECT_CALL(*notePhonemeMapper, find(key.noteNumber, key.velocity))
                .Times(1)
                .WillOnce(ReturnRef(items));

        bool result = WaveformCorpus(
                    CorpusMeta(QString("test"), QString(), QString(), QString(), QString()),
                    QSharedPointer<NotePhonemeMapper>(notePhonemeMapper),
                    phonemeRepositories,
                    QSharedPointer<PhonemeSelector>(phonemeSelector)
                ).contains(key);
        QCOMPARE(result, true);
    }
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
        NotePhonemeMappingItem item1("1", 1.0);
        NotePhonemeMappingItem item2("2", 0.0);
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
        PhonemeKey key("pronounce", 1.0, 100.0, velocity, noteNumber);
        EXPECT_CALL(*mockedPhonemeMapper, find(noteNumber, velocity))
                .WillOnce(ReturnRef(items))
                .WillOnce(ReturnRef(items));

        EXPECT_CALL(*mockedPhonemeRepository1, find(key.pronounce))
                .WillOnce(Return(phonemes[0]));

        EXPECT_CALL(*mockedPhonemeRepository2, find(key.pronounce))
                .WillOnce(Return(phonemes[1]));

        EXPECT_CALL(*selector, select(key.msPosition, items, phonemes))
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
        NotePhonemeMappingItem item1("1", 1.0);
        NotePhonemeMappingItem item2("2", 0.0);
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

        EXPECT_CALL(*selector, select(_, _, _))
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
