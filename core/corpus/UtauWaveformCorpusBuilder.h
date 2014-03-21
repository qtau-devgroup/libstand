/* UtauWaveformCorpusBuilder.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef UTAUWAVEFORMCORPUSBUILDER_H
#define UTAUWAVEFORMCORPUSBUILDER_H

#include <QMap>

#include "corpus/UtauCharacterInfoConverter.h"
#include "corpus/WaveformCorpusBuilder.h"
#include "utau/UtauVoicebank.h"

namespace stand
{

/**
 * @brief The UtauWaveformCorpusBuilder class is a builder class of WaveformCorpus.
 *        This class uses UTAU voicebank to build WaveformCorpus.
 *        It requires an id for each phoneme repository and velocity-note mapping.
 * @author Hal@shurabaP
 */
class UtauWaveformCorpusBuilder : public WaveformCorpusBuilder
{
public:
    UtauWaveformCorpusBuilder(
            const UtauVoicebank utau,
            QSharedPointer<ResourceFactory<QString, Signal> > signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(new WaveFileSignalFactory),
            QSharedPointer<UtauPhonemeConverter> phonemeConverter = QSharedPointer<UtauPhonemeConverter>(new UtauPhonemeConverter),
            QSharedPointer<UtauCharacterInfoConverter> characterConverter = QSharedPointer<UtauCharacterInfoConverter>(new UtauCharacterInfoConverter)
            );
    virtual ~UtauWaveformCorpusBuilder(){ }

    /**
     * @brief setId sets id to the UTAU oto.ini specified by `directory`.
     * @param id is an identifier.
     * @param directory specifies which oto.ini to set id.
     * @param suffix in each phoneme.
     * @return true if directory found, otherwise false.
     */
    bool setId(const QString &id, const QDir &directory, const QString suffix);
private:
    const UtauVoicebank utau;
};

}

#endif // UTAUWAVEFORMCORPUSBUILDER_H
