/* PhonemeSelector.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef PHONEMESELECTORTEST_H
#define PHONEMESELECTORTEST_H

#include <QTest>

#include "corpus/NotePhonemeMapper.h"
#include "corpus/PhonemeSelector.h"

#include "AutoTest.h"

namespace stand
{

class PhonemeSelectorTest : public QObject
{
    Q_OBJECT
private slots:
    void select_should_return_empty_data_if_called_with_empty_list()
    {
        PhonemeSelector selector;
        QCOMPARE(selector.select(NotePhonemeMappingList(), QList<QSharedPointer<Phoneme> >())->isEmpty(), true);
    }
    void select_should_return_proper_phonemes()
    {
        QList<QSharedPointer<Phoneme> > phonemes;
        phonemes.append(QSharedPointer<Phoneme>(new Phoneme("test", 0, 500, 500, 0, 0)));
        NotePhonemeMappingList list;
        list.append(NotePhonemeMappingItem("hoge", 20, 1.0));
        PhonemeSelector selector;
        WaveformFrameInfoList expected;
        WaveformFrameInfo info(phonemes.at(0)->filename, phonemes.at(0)->msBegin + list.at(0).msPosition, list.at(0).amplify);
        expected.append(info);
        auto result = selector.select(list, phonemes);
        QCOMPARE(*result, expected);
    }
    void select_should_mix_phonemes_with_specified_ratio()
    {
        QList<QSharedPointer<Phoneme> > phonemes;
        phonemes.append(QSharedPointer<Phoneme>(new Phoneme("test1", 0, 500, 500, 0, 0)));
        phonemes.append(QSharedPointer<Phoneme>(new Phoneme("test2", 0, 500, 500, 0, 0)));
        NotePhonemeMappingList list;
        list.append(NotePhonemeMappingItem("hoge1", 20, 0.3));
        list.append(NotePhonemeMappingItem("hoge2", 20, 0.7));
        PhonemeSelector selector;
        WaveformFrameInfoList expected;
        WaveformFrameInfo info1(phonemes.at(0)->filename, phonemes.at(0)->msBegin + list.at(0).msPosition, list.at(0).amplify);
        WaveformFrameInfo info2(phonemes.at(1)->filename, phonemes.at(1)->msBegin + list.at(1).msPosition, list.at(1).amplify);
        expected.append(info1);
        expected.append(info2);
        auto result = selector.select(list, phonemes);
        QCOMPARE(*result, expected);
    }
    void select_should_mix_phoneme_by_proper_ratio_with_looped_position()
    {
        QList<QSharedPointer<Phoneme> > phonemes;
        phonemes.append(QSharedPointer<Phoneme>(new Phoneme("test", 200, 500, 0, 0, 0)));
        NotePhonemeMappingList list;
        list.append(NotePhonemeMappingItem("hoge", 200, 0.8));
        PhonemeSelector selector;
        WaveformFrameInfoList expected;
        double ratio = (list.at(0).msPosition - phonemes.at(0)->msFixedLength) / (phonemes.at(0)->msLength - phonemes.at(0)->msFixedLength);
        WaveformFrameInfo info1(
                    phonemes.at(0)->filename,
                    phonemes.at(0)->msBegin + list.at(0).msPosition,
                    list.at(0).amplify * (1.0 - ratio);
        WaveformFrameInfo info2(
                    phonemes.at(0)->filename,
                    phonemes.at(0)->msBegin + phonemes.at(0)->msLength - list.at(0).msPosition,
                    list.at(0).amplify * ratio);
        expected.append(info1);
        expected.append(info2);
        auto result = selector.select(list, phonemes);
        QCOMPARE(*result, expected);
    }
};

}

DECLARE_TEST(stand::PhonemeSelectorTest)

#endif // PHONEMESELECTORTEST_H
