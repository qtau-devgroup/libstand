/* WaveformCorpus.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WAVEFORMCORPUS_H
#define WAVEFORMCORPUS_H

#include <QHash>
#include <QSharedPointer>

#include "corpus/NotePhonemeMapper.h"
#include "corpus/Phoneme.h"
#include "corpus/PhonemeKey.h"
#include "corpus/PhonemeSelector.h"
#include "corpus/WaveformFrameInfoList.h"
#include "util/ResourceRepository.h"

namespace stand
{

/**
 * @brief The WaveformCorpus class is a repository class for phoneme.
 * @author Hal@shurabaP
 */
class WaveformCorpus : public ResourceRepository<PhonemeKey, WaveformFrameInfoList>
{
public:
    explicit WaveformCorpus(
        const QSharedPointer<NotePhonemeMapper> phonemeMapper,
        const QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories,
        const QSharedPointer<PhonemeSelector> selector
    );
    WaveformCorpus(const WaveformCorpus &other);
    virtual ~WaveformCorpus(){ }

    /**
     * @brief find returns the pointer corresponding to `key`.
     * @param key
     * @return corresponding resource. null for non-existing key.
     */
    virtual const QSharedPointer<WaveformFrameInfoList> find(const PhonemeKey &key) const;

    /**
     * @brief contains returns true only when phonemeRepositories contain all the id that phonemeMapper finds.
     */
    virtual bool contains(const PhonemeKey &key) const;

    /**
     * @brief add does nothing in this class. (Unsupported operation)
     * @param key for value.
     * @param value is a resource.
     * @return false always.
     */
    virtual bool add(const PhonemeKey &key, QSharedPointer<WaveformFrameInfoList> value);

    /**
     * @brief remove does nothing. (Unsupported operation)
     */
    virtual void remove(const PhonemeKey &key);

private:
    const QSharedPointer<NotePhonemeMapper> phonemeMapper;
    const QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
    const QSharedPointer<PhonemeSelector> selector;
};

}

#endif // WAVEFORMCORPUS_H
