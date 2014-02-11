/* WorldFrameRepository.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMEREPOSITORY_H
#define WORLDFRAMEREPOSITORY_H

#include <QFileInfo>

#include "corpus/PhonemeKey.h"
#include "corpus/WaveformFrameInfoList.h"
#include "synthesis/world/WorldFrame.h"
#include "synthesis/world/WorldFrameAnalyzer.h"
#include "synthesis/world/WorldWaveform.h"
#include "util/ResourceRepository.h"

namespace stand
{

/**
 * @brief The WorldFrameRepository class is a repository class for WorldFrame.
 *        WorldFrame is a big sized instance, so WorldFrameRepository does not keep any frame.
 *        All WorldFrame is calculated from WorldWaveform and then WorldFrameRepository::find returns.
 * @author Hal@shurabaP
 */
class WorldFrameRepository : public ResourceRepository<PhonemeKey, WorldFrame>
{
public:
    WorldFrameRepository(
        QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > waveformInfoRepository,
        QSharedPointer<ResourceRepository<QString, WorldWaveform> > waveformRepository,
        QSharedPointer<WorldFrameAnalyzer> frameAnalyzer = QSharedPointer<WorldFrameAnalyzer>(new WorldFrameAnalyzer)
    );

    virtual ~WorldFrameRepository(){ }

    /**
     * @brief find returns the pointer corresponding to `key`.
     * @param key
     * @return corresponding resource. null for non-existing key.
     */
    virtual const QSharedPointer<WorldFrame> find(const PhonemeKey &key) const;

    /**
     * @brief contains returns if `key` exists int this collection.
     */
    virtual bool contains(const PhonemeKey &key) const;

    /**
     * @brief WorldFrameRepository does not support `add` method because WorldFrame is dynamically generated.
     * @param key for value.
     * @param value is a resource.
     * @return always false.
     */
    virtual bool add(const PhonemeKey &key, QSharedPointer<WorldFrame> value) ;

    /**
     * @brief remove do nothing.
     */
    virtual void remove(const PhonemeKey &key);
protected:
    QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > waveformInfoRepository;
    QSharedPointer<ResourceRepository<QString, WorldWaveform> > waveformRepository;
    QSharedPointer<WorldFrameAnalyzer> frameAnalyzer;
};

}

#endif // WORLDFRAMEREPOSITORY_H
