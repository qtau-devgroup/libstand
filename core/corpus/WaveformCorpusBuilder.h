/* WaveformCorpusBuilder.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WAVEFORMCORPUSBUILDER_H
#define WAVEFORMCORPUSBUILDER_H

#include "corpus/NotePhonemeMapper.h"
#include "corpus/UtauPhonemeConverter.h"
#include "corpus/WaveformCorpus.h"
#include "dsp/WaveFileSignalFactory.h"
#include "utau/UtauOtoHash.h"

#include <QSharedPointer>

namespace stand
{

/**
 * @brief The WaveformCorpusBuilder class is a builder class of WaveformCorpus.
 *        WaveformCorpusBuilder builds WaveformCorpus from the given data.
 * @author Hal@shurabaP
 */
class WaveformCorpusBuilder
{
public:
    /**
     * @brief WaveformCorpusBuilder
     * @param meta is a meta information for the corpus.
     * @param signalFactory creates signal from given QString.
     * @param converter converts UtauPhoneme into STAND Phoneme.
     */
    WaveformCorpusBuilder(
            const CorpusMeta &meta,
            QSharedPointer<ResourceFactory<QString, Signal> > signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(new WaveFileSignalFactory),
            QSharedPointer<UtauPhonemeConverter> converter = QSharedPointer<UtauPhonemeConverter>(new UtauPhonemeConverter),
            QSharedPointer<NotePhonemeMapper> phonemeMapper = QSharedPointer<NotePhonemeMapper>(new NotePhonemeMapper)
            );
    virtual ~WaveformCorpusBuilder(){ }

    /**
     * @brief add adds a single phoneme repository specified by `id` from `oto`.
     *        The specified suffix will be removed from all the phoneme in UtauOtoHash.
     * @param id is an identifier for the repository.
     *        If the given `id` exists in this builder, `add` method does nothing.
     * @param oto is a utau voice bank from oto.ini.
     * @param suffix
     * @return the reference of this instance.
     */
    WaveformCorpusBuilder &add(const QString &id, const UtauOtoHash &oto, const QString &suffix = QString(""));
    /**
     * @brief add adds a single PhonemeRepository specified by `id`.
     * @param id is an identifier.
     *        If the given `id` exitsts in this builder, `add` method does nothing.
     * @param phonemeRepository to add.
     * @return the reference of this instance.
     */
    WaveformCorpusBuilder &add(const QString &id, QSharedPointer<ResourceRepository<QString, Phoneme> > &phonemeRepository);
    /**
     * @brief setMapper sets the mapper.
     * @param mapper is a mapping of samples.
     * @return the reference of this instance.
     */
    WaveformCorpusBuilder &setMapper(QSharedPointer<NotePhonemeMapper> mapper);
    /**
     * @brief setMappingElement sets a single element of sample mapping.
     * @param note is a note number.
     * @param velocity is a velocity.
     * @param element to set.
     * @return the reference of this instance.
     */
    WaveformCorpusBuilder &setMappingElement(int note, int velocity, const NotePhonemeMappingList &element);
    /**
     * @brief addMappingItem adds a single item for the specified mapping element.
     * @param note is a note number.
     * @param velocity is a velocity.
     * @param item to add.
     * @return the reference of this instance.
     */
    WaveformCorpusBuilder &addMappingItem(int note, int velocity, const NotePhonemeMappingItem &item);

    /**
     * @brief build WaveformCorpus with data in this instance.
     * @param selector selects waveform position from phonemes.
     * @return WaveformCorpus.
     *         If QSharedPointer is null, WaveformCorpusBuilder fails to build a corpus.
     */
    virtual QSharedPointer<WaveformCorpus> build(const QSharedPointer<PhonemeSelector> selector);
private:
    CorpusMeta meta;
    QSharedPointer<NotePhonemeMapper> phonemeMapper;
    QSharedPointer<ResourceFactory<QString, Signal> > signalFactory;
    QSharedPointer<UtauPhonemeConverter> converter;

    QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
};

}

#endif // WAVEFORMCORPUSBUILDER_H
