/* PhonemeRepository.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef PHONEMEREPOSITORY_H
#define PHONEMEREPOSITORY_H

#include "corpus/Phoneme.h"
#include "util/ResourceRepository.h"

namespace stand
{

/**
 * @brief The PhonemeRepository class is a repository class of Phoneme.
 *        This class keeps Phonemes in hash-map.
 * @author Hal@shurabaP
 */
class PhonemeRepository : public ResourceRepository<QString, Phoneme>
{
public:
    ~PhonemeRepository(){ }
    /**
     * @brief find returns Phoneme if this class has the `key`
     * @param key to find.
     * @return Phoneme when finds key, otherwise null.
     */
    const QSharedPointer<Phoneme> find(const QString &key) const;

    /**
     * @brief contains return whether this class has the `key`.
     * @param key to find.
     * @return whether the key exists.
     */
    bool contains(const QString &key) const;

    /**
     * @brief add Phoneme with key. If key exists, this method will fail.
     * @param key to add with.
     * @param value to add.
     * @return whether `add` succeeds.
     */
    bool add(const QString &key, QSharedPointer<Phoneme> value);

    /**
     * @brief remove the `key`
     * @param key to remove.
     */
    void remove(const QString &key);


    /**
     * @brief toJson converts this instance to QJsonValue.
     * @return QJsonValue
     */
    QJsonValue toJson() const;

    /**
     * @brief fromJson is a factory method of PhonemeRepository from JSON.
     * @param json to read.
     * @return QSharedPointer<PhonemeRepository> if succeeded, otherwise null.
     */
    static QSharedPointer<ResourceRepository<QString, Phoneme> > fromJson(const QJsonValue &json);

private:
    QHash<QString, QSharedPointer<Phoneme> > dictionary;
};

}

#endif // PHONEMEREPOSITORY_H
