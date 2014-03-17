/* WaveformCorpus.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "WaveformCorpus.h"

using namespace stand;

WaveformCorpus::WaveformCorpus(
    const CorpusMeta &meta,
    const QSharedPointer<NotePhonemeMapper> phonemeMapper,
    const QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories,
    const QSharedPointer<PhonemeSelector> selector
) : meta(meta), phonemeMapper(phonemeMapper), phonemeRepositories(phonemeRepositories), selector(selector)
{
}

WaveformCorpus::WaveformCorpus(const WaveformCorpus &other) :
    WaveformCorpus(other.meta, other.phonemeMapper, other.phonemeRepositories, other.selector)
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
        phonemes.append(phonemeRepositories[item.id]->find(key.pronounce));
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
