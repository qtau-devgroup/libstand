/* WaveformCorpusBuilder.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "corpus/PhonemeRepository.h"

#include "WaveformCorpusBuilder.h"

using namespace stand;

WaveformCorpusBuilder::WaveformCorpusBuilder(const CorpusMeta &meta, QSharedPointer<ResourceFactory<QString, Signal> > signalFactory, QSharedPointer<UtauPhonemeConverter> converter) :
    meta(meta), signalFactory(signalFactory), converter(converter), phonemeMapper(new NotePhonemeMapper())
{
}

WaveformCorpusBuilder &WaveformCorpusBuilder::add(const QString &id, const UtauOtoHash &oto, const QString &suffix)
{
    if(converter.isNull() || signalFactory.isNull() || phonemeRepositories.contains(id))
    {
        return *this;
    }

    QSharedPointer<ResourceRepository<QString, Phoneme> > repository = QSharedPointer<ResourceRepository<QString, Phoneme> >(new PhonemeRepository);
    foreach(const UtauPhoneme &phoneme, oto.values())
    {
        QString pronounce(phoneme.pronounce);
        pronounce.remove(suffix + "$");
        repository->add(pronounce, converter->convert(phoneme, oto.directory(), signalFactory));
    }
    phonemeRepositories.insert(id, QSharedPointer<ResourceRepository<QString, Phoneme> >(repository));
    return *this;
}

WaveformCorpusBuilder &WaveformCorpusBuilder::add(const QString &id, QSharedPointer<ResourceRepository<QString, Phoneme> > &phonemeRepository)
{
    if(phonemeRepositories.contains(id))
    {
        return *this;
    }
    phonemeRepositories.insert(id, phonemeRepository);
    return *this;
}

WaveformCorpusBuilder &WaveformCorpusBuilder::setMapper(QSharedPointer<NotePhonemeMapper> mapper)
{
    phonemeMapper = mapper;
    return *this;
}

WaveformCorpusBuilder &WaveformCorpusBuilder::setMappingElement(int note, int velocity, const NotePhonemeMappingList &element)
{
    if(note < 0 || 128 <= note || velocity < 0 || 128 <= note)
    {
        return *this;
    }
    (*phonemeMapper)[note][velocity] = element;
    return *this;
}

WaveformCorpusBuilder &WaveformCorpusBuilder::addMappingItem(int note, int velocity, const NotePhonemeMappingItem &item)
{
    if(note < 0 || 128 <= note || velocity < 0 || 128 <= note)
    {
        return *this;
    }
    (*phonemeMapper)[note][velocity].append(item);
    return *this;
}

QSharedPointer<WaveformCorpus> WaveformCorpusBuilder::build(const QSharedPointer<PhonemeSelector> selector)
{
    return QSharedPointer<WaveformCorpus>(new WaveformCorpus(meta, phonemeMapper, phonemeRepositories, selector));
}
