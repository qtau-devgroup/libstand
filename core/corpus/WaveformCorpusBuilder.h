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
 * @author Hal@shurabaP
 */
class WaveformCorpusBuilder
{
public:
    explicit WaveformCorpusBuilder(
            QSharedPointer<ResourceFactory<QString, Signal> > signalFactory = QSharedPointer<ResourceFactory<QString, Signal> >(new WaveFileSignalFactory),
            QSharedPointer<UtauPhonemeConverter> converter = QSharedPointer<UtauPhonemeConverter>(new UtauPhonemeConverter)
            );
    virtual ~WaveformCorpusBuilder(){ }

    WaveformCorpusBuilder &add(const QString &id, const UtauOtoHash &oto, const QString &suffix = QString(""));
    WaveformCorpusBuilder &add(const QString &id, QSharedPointer<ResourceRepository<QString, Phoneme> > &phonemeRepository);
    WaveformCorpusBuilder &setMapper(QSharedPointer<NotePhonemeMapper> mapper);
    WaveformCorpusBuilder &setMappingElement(int note, int velocity, const NotePhonemeMappingList &element);
    WaveformCorpusBuilder &addMappingItem(int note, int velocity, const NotePhonemeMappingItem &item);

    virtual QSharedPointer<WaveformCorpus> build(const QSharedPointer<PhonemeSelector> selector);
private:
    QSharedPointer<ResourceFactory<QString, Signal> > signalFactory;
    QSharedPointer<UtauPhonemeConverter> converter;
    QSharedPointer<NotePhonemeMapper> phonemeMapper;
    QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
};

}

#endif // WAVEFORMCORPUSBUILDER_H
