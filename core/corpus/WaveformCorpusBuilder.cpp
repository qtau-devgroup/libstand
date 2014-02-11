/* WaveformCorpusBuilder.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "corpus/PhonemeRepository.h"

#include "WaveformCorpusBuilder.h"

using namespace stand;

WaveformCorpusBuilder::WaveformCorpusBuilder() :
    phonemeMapper(new NotePhonemeMapper())
{
}

WaveformCorpusBuilder &WaveformCorpusBuilder::add(const QString &id, const UtauOtoHash &oto, const QDir &baseDirectory, const QString &suffix)
{
    if(phonemeRepositories.contains(id))
    {
        return *this;
    }
    QSharedPointer<ResourceRepository<QString, Phoneme> > repository = QSharedPointer<ResourceRepository<QString, Phoneme> >(new PhonemeRepository);
    foreach(const UtauPhoneme &phoneme, oto.values())
    {
        double msLength;
        if(phoneme.msRightBlank < 0)
        {
            msLength = -phoneme.msRightBlank;
        }
        else
        {
            // get msLength from WAVE.
        }
        QString pronounce(phoneme.pronounce);
        pronounce.remove(suffix);
        QString filepath(baseDirectory.relativeFilePath(phoneme.filename));
        QSharedPointer<Phoneme> p(new Phoneme(filepath, phoneme.msLeftBlank, msLength, phoneme.msFixedLength, phoneme.msPreutterance, phoneme.msOverlap));
        repository->add(pronounce, p);
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
    return QSharedPointer<WaveformCorpus>(new WaveformCorpus(phonemeMapper, phonemeRepositories, selector));
}
