/* PhonemeSelector.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "PhonemeSelector.h"

using namespace stand;

QSharedPointer<WaveformFrameInfoList> PhonemeSelector::select(double msPosition, const NotePhonemeMappingList &items, const QList<QSharedPointer<Phoneme> > &phonemes) const
{
    if(items.size() != phonemes.size())
    {
        return QSharedPointer<WaveformFrameInfoList>();
    }

    WaveformFrameInfoList *result = new WaveformFrameInfoList;
    for(int i = 0; i < items.size(); i++)
    {
        *result += fromOnePhoneme(msPosition, items[i], phonemes[i]);
    }
    return QSharedPointer<WaveformFrameInfoList>(result);
}

WaveformFrameInfoList PhonemeSelector::fromOnePhoneme(double msPosition, const NotePhonemeMappingItem &item, const QSharedPointer<Phoneme> &phoneme) const
{
    WaveformFrameInfoList result;
    double msFixedEndRelativePosition = (phoneme->msFixedLength - phoneme->msPreutterance);
    if(msPosition < msFixedEndRelativePosition)
    {
        result.append(WaveformFrameInfo(phoneme->filename, phoneme->msBegin + msPosition, item.amplify));
    }
    else
    {
        double msLoopLength = (phoneme->msLength - phoneme->msFixedLength);
        double msFixedEndAbsolutePosition = phoneme->msBegin + phoneme->msFixedLength;
        double msModPosition = fmod(msPosition - msFixedEndRelativePosition, msLoopLength);
        double msCurrentPosition = msFixedEndAbsolutePosition + msModPosition;
        double msCounterPosition = msFixedEndAbsolutePosition + msLoopLength - msModPosition;
        double ratio = msModPosition / msLoopLength;
        result.append(WaveformFrameInfo(phoneme->filename, msCurrentPosition, item.amplify * (1.0 - ratio)));
        result.append(WaveformFrameInfo(phoneme->filename, msCounterPosition, item.amplify * ratio));
    }
    return result;
}
