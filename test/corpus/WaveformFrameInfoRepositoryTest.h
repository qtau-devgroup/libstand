/* WaveformCorpusTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WAVEFORMFRAMEINFOREPOSITORYTEST_H
#define WAVEFORMFRAMEINFOREPOSITORYTEST_H

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
    MockNotePhonemeMapper(const QList<QList<NotePhonemeMappingList> > &elementTable) : NotePhonemeMapper(elementTable){ }
    MOCK_CONST_METHOD2_T(find, const NotePhonemeMappingList &(int note, int velocity));
};

class MockPhonemeSelector : public PhonemeSelector
{
public:
    MOCK_CONST_METHOD2_T(select, QSharedPointer<WaveformFrameInfoList>(const NotePhonemeMappingList &items, QList<QSharedPointer<Phoneme> > &phonemes));
};

class WaveformCorpusTest : public QObject
{
    Q_OBJECT
private slots:
    void contains_should_return_true_in()
    {
        QList<QList<NotePhonemeMappingList> > elementTable;
        MockNotePhonemeMapper *notePhonemeMapper = new MockNotePhonemeMapper(elementTable);
        MockPhonemeSelector *phonemeSelector = new MockPhonemeSelector;
        MockResourceRepository<QString, Phoneme> *phonemeRepository1 = new MockResourceRepository<QString, Phoneme>;
        MockResourceRepository<QString, Phoneme> *phonemeRepository2 = new MockResourceRepository<QString, Phoneme>;
        QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
        phonemeRepositories.insert("1", QSharedPointer<ResourceRepository<QString, Phoneme> >(phonemeRepository1));
        phonemeRepositories.insert("2", QSharedPointer<ResourceRepository<QString, Phoneme> >(phonemeRepository2));
        NotePhonemeMappingList items;
        items.append(NotePhonemeMappingItem("1", 0, 0.5));
        items.append(NotePhonemeMappingItem("2", 0, 0.5));

        PhonemeKey key("test", 1.0, 0.0, 32, 64);
        EXPECT_CALL(*notePhonemeMapper, find(key.noteNumber, key.velocity))
                .Times(1)
                .WillOnce(ReturnRef(items));

        bool result = WaveformCorpus(
                        QSharedPointer<NotePhonemeMapper>(notePhonemeMapper),
                        phonemeRepositories,
                        QSharedPointer<PhonemeSelector>(phonemeSelector)
                    ).contains(key);
        QCOMPARE(result, true);
    }

    void find_should_return_proper_result_in()
    {
        QList<QList<NotePhonemeMappingList> > elementTable;
        MockNotePhonemeMapper *notePhonemeMapper = new MockNotePhonemeMapper(elementTable);
        MockPhonemeSelector *phonemeSelector = new MockPhonemeSelector;
        MockResourceRepository<QString, Phoneme> *phonemeRepository1 = new MockResourceRepository<QString, Phoneme>;
        MockResourceRepository<QString, Phoneme> *phonemeRepository2 = new MockResourceRepository<QString, Phoneme>;
        QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
        phonemeRepositories.insert("phoneme1", QSharedPointer<ResourceRepository<QString, Phoneme> >(phonemeRepository1));
        phonemeRepositories.insert("phoneme2", QSharedPointer<ResourceRepository<QString, Phoneme> >(phonemeRepository2));
        Phoneme *phoneme1 = new Phoneme("phoneme1", 0, 0, 0, 0, 0);
        Phoneme *phoneme2 = new Phoneme("phoneme2", 1, 1, 1, 1, 1);
        QList<QSharedPointer<Phoneme> > phonemes;
        phonemes.append(QSharedPointer<Phoneme>(phoneme1));
        phonemes.append(QSharedPointer<Phoneme>(phoneme2));
        NotePhonemeMappingList items;
        items.append(NotePhonemeMappingItem("phoneme1", 0, 0.5));
        items.append(NotePhonemeMappingItem("phoneme2", 0, 0.5));
        QSharedPointer<WaveformFrameInfoList> frameInfoList = QSharedPointer<WaveformFrameInfoList>(new WaveformFrameInfoList);

        PhonemeKey key("test", 1.0, 0.0, 32, 64);
        EXPECT_CALL(*notePhonemeMapper, find(key.noteNumber, key.velocity))
                .Times(2)
                .WillOnce(ReturnRef(items))
                .WillOnce(ReturnRef(items));
        EXPECT_CALL(*phonemeRepository1, find(key.pronounce))
                .Times(1)
                .WillOnce(Return(phonemes[0]));
        EXPECT_CALL(*phonemeRepository2, find(key.pronounce))
                .Times(1)
                .WillOnce(Return(phonemes[1]));
        EXPECT_CALL(*phonemeSelector, select(items, phonemes))
                .Times(1)
                .WillOnce(Return(frameInfoList));

        WaveformCorpus repos(WaveformCorpus(
                    QSharedPointer<NotePhonemeMapper>(notePhonemeMapper),
                    phonemeRepositories,
                    QSharedPointer<PhonemeSelector>(phonemeSelector)
                );
        auto result = repos.find(key);

        QCOMPARE(result, frameInfoList);
    }
};

}

DECLARE_TEST(stand::WaveformCorpusTest)

#endif // WAVEFORMFRAMEINFOREPOSITORYTEST_H
