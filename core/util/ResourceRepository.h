/* ResourceRepository.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef RESOURCEREPOSITORY_H
#define RESOURCEREPOSITORY_H

#include <QSharedPointer>

namespace stand
{

/**
 * @brief The ResourceFactory class is a factory class of Resource.
 * @tparam Key is a key type.
 * @tparam T is a resource type.
 * @author Hal@shurabaP
 */
template <class Key, class T> class ResourceFactory
{
public:
    virtual ~ResourceFactory(){ }

    /**
     * @brief create creates a value T from the given key.
     * @param key is a key for created item.
     * @return the created resource.
     */
    virtual T create(const Key &key) = 0;
};

/**
 * @brief The ResourceRepository class represents a repository for resource.
 *        ResourceRepository creates, reads, updates, and deletes a resource.
 * @tparam Key is a key type.
 * @tparam T is a resource type.
 * @author Hal@shurabaP
 */
template <class Key, class T> class ResourceRepository
{
public:
    /**
     * @brief ResourceRepository is a constructor.
     * @param factory is a factory class for resource.
     */
    explicit ResourceRepository(QSharedPointer<ResourceFactory<Key, QSharedPointer<T> > > factory = QSharedPointer<ResourceFactory<Key, QSharedPointer<T> > >()) : factory(factory){ }

    virtual ~ResourceRepository(){ }

    /**
     * @brief find returns the pointer corresponding to `key`.
     * @param key
     * @return corresponding resource. null for non-existing key.
     */
    virtual const QSharedPointer<T> find(const Key &key) const = 0;

    /**
     * @brief contains returns if `key` exists int this collection.
     */
    virtual bool contains(const Key &key) const = 0;

    /**
     * @brief add adds `value` into this collection.
     * @param key for value.
     * @param value is a resource.
     * @return true for success, false for failure.
     */
    virtual bool add(const Key &key, QSharedPointer<T> value) = 0;

    /**
     * @brief add adds key into this collection.
     *        ResourceRepository should create the value for key.
     *        If no factory class given to the constructor, this method always fails.
     * @param key
     * @return true for success, false for failure.
     */
    bool add(const Key &key);

    /**
     * @brief remove resource corresponding to key.
     */
    virtual void remove(const Key &key) = 0;
private:
    QSharedPointer<ResourceFactory<Key, QSharedPointer<T> > > factory;
};

}

#endif // RESOURCEREPOSITORY_H
