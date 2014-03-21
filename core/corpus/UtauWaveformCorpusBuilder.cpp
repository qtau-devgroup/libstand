/* UtauWaveformCorpusBuilder.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include "utau/UtauOtoHash.h"

#include "UtauWaveformCorpusBuilder.h"

using namespace stand;

UtauWaveformCorpusBuilder::UtauWaveformCorpusBuilder(
        const UtauVoicebank utau,
        QSharedPointer<ResourceFactory<QString, Signal> > signalFactory,
        QSharedPointer<UtauPhonemeConverter> phonemeConverter,
        QSharedPointer<UtauCharacterInfoConverter> characterConverter
    ) : WaveformCorpusBuilder(characterConverter->convert(utau.root, utau.characterInfo), signalFactory, phonemeConverter), utau(utau)
{
}

bool UtauWaveformCorpusBuilder::setId(const QString &id, const QDir &directory, const QString suffix)
{
    foreach(const auto &oto, utau.otos)
    {
        if(directory == oto.directory())
        {
            add(id, oto, suffix);
            return true;
        }
    }
    return false;
}
