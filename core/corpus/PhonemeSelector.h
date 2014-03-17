/* PhonemeSelector.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef PHONEMESELECTOR_H
#define PHONEMESELECTOR_H

#include <QSharedPointer>

#include "corpus/NotePhonemeMapper.h"
#include "corpus/Phoneme.h"
#include "corpus/WaveformFrameInfoList.h"

namespace stand
{

/**
 * @brief The PhonemeSelector class selects a proper timing of phonemes.
 * @author Hal@shurabaP
 */
class PhonemeSelector
{
public:
    virtual ~PhonemeSelector(){ }
    virtual QSharedPointer<WaveformFrameInfoList> select(const NotePhonemeMappingList &items, const QList<QSharedPointer<Phoneme> > &phonemes) const;
private:
    WaveformFrameInfoList fromOnePhoneme(const NotePhonemeMappingItem &item, const QSharedPointer<Phoneme> &phoneme) const;
};

}

#endif // PHONEMESELECTOR_H
