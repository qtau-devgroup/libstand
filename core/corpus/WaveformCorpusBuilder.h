/* WaveformCorpusBuilder.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WAVEFORMCORPUSBUILDER_H
#define WAVEFORMCORPUSBUILDER_H

#include "corpus/NotePhonemeMapper.h"
#include "corpus/WaveformCorpus.h"
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
    WaveformCorpusBuilder();
    virtual ~WaveformCorpusBuilder(){ }

    WaveformCorpusBuilder &add(const QString &id, const UtauOtoHash &oto, const QDir &baseDirectory, const QString &suffix = QString(""));
    WaveformCorpusBuilder &add(const QString &id, QSharedPointer<ResourceRepository<QString, Phoneme> > &phonemeRepository);
    WaveformCorpusBuilder &setMapper(QSharedPointer<NotePhonemeMapper> mapper);
    WaveformCorpusBuilder &setMappingElement(int note, int velocity, const NotePhonemeMappingList &element);
    WaveformCorpusBuilder &addMappingItem(int note, int velocity, const NotePhonemeMappingItem &item);

    virtual QSharedPointer<WaveformCorpus> build(const QSharedPointer<PhonemeSelector> selector);
private:
    QSharedPointer<NotePhonemeMapper> phonemeMapper;
    QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
};

}

#endif // WAVEFORMCORPUSBUILDER_H
