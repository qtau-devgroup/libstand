/* WorldWaveformRepository.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDWAVEFORMREPOSITORY_H
#define WORLDWAVEFORMREPOSITORY_H

#include <QString>
#include <QHash>

#include "synthesis/world/WorldWaveform.h"
#include "util/ResourceRepository.h"

namespace stand
{

/**
 * @brief The WorldWaveformRepository class is a repository for WorldWaveform.
 *        This class is a simple wrapper class of QHash<QString, QSharedPointer<WorldWaveform> >.
 * @author Hal@shurabaP
 */
class WorldWaveformRepository : public ResourceRepository<QString, WorldWaveform>
{
public:
    /**
     * @brief WorldWaveformRepository is a constructor.
     * @param factory is a factory class for WorldWaveform.
     */
    explicit WorldWaveformRepository(
        QSharedPointer<ResourceFactory<QString, QSharedPointer<WorldWaveform> > > factory = QSharedPointer<ResourceFactory<QString, WorldWaveform> >()
    );

    virtual ~WorldWaveformRepository(){ }

    /**
     * @brief find returns the pointer corresponding to `key`.
     * @param key
     * @return corresponding resource. null for non-existing key.
     */
    virtual const QSharedPointer<WorldWaveform> find(const QString &key) const;

    /**
     * @brief contains returns if `key` exists int this collection.
     */
    virtual bool contains(const QString &key) const;

    /**
     * @brief add adds `value` into this collection.
     * @param key for value.
     * @param value is a resource.
     * @return true for success, false for failure.
     */
    virtual bool add(const QString &key, QSharedPointer<WorldWaveform> value);

    /**
     * @brief remove resource corresponding to key.
     */
    virtual void remove(const QString &key);
private:
    QHash<QString, QSharedPointer<WorldWaveform> > dictionary;
};

}

#endif // WORLDWAVEFORMREPOSITORY_H
