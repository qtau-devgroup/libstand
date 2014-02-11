/* WaveformCorpus.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "WaveformCorpus.h"

using namespace stand;

WaveformCorpus::WaveformCorpus(
    const QSharedPointer<NotePhonemeMapper> phonemeMapper,
    const QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories,
    const QSharedPointer<PhonemeSelector> selector
) : phonemeMapper(phonemeMapper), phonemeRepositories(phonemeRepositories), selector(selector)
{
}

WaveformCorpus::WaveformCorpus(const WaveformCorpus &other) :
    WaveformCorpus(other.phonemeMapper, other.phonemeRepositories, other.selector)
{
}

const QSharedPointer<WaveformFrameInfoList> WaveformCorpus::find(const PhonemeKey &key) const
{
    if(!contains(key))
    {
        return QSharedPointer<WaveformFrameInfoList>();
    }
    // contain should ensure that all ids in items should exist in phonemeRepositories.
    const NotePhonemeMappingList &items = phonemeMapper->find(key.noteNumber, key.velocity);
    QList<QSharedPointer<Phoneme> > phonemes;
    foreach(const auto &item, items)
    {
        const QSharedPointer<ResourceRepository<QString, Phoneme> > &repository(phonemeRepositories.find(item.id).value());
        phonemes.append(repository->find(key.pronounce));
    }
    return selector->select(items, phonemes);
}

bool WaveformCorpus::contains(const PhonemeKey &key) const
{
    const auto &items = phonemeMapper->find(key.noteNumber, key.velocity);
    bool result = true;
    foreach(const auto &item, items)
    {
        result &= phonemeRepositories.contains(item.id);
    }
    result &= !items.empty();
    return result;
}

bool WaveformCorpus::add(const PhonemeKey &/*key*/, QSharedPointer<WaveformFrameInfoList> /*value*/)
{
    return false;
}

void WaveformCorpus::remove(const PhonemeKey &/*key*/)
{
}
