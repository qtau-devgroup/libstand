/* PhonemeRepository.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "PhonemeRepository.h"

using namespace stand;

const QSharedPointer<Phoneme> PhonemeRepository::find(const QString &key) const
{
    if(!contains(key))
    {
        return QSharedPointer<Phoneme>();
    }
    return dictionary.value(key);
}

bool PhonemeRepository::contains(const QString &key) const
{
    return dictionary.contains(key);
}

bool PhonemeRepository::add(const QString &key, QSharedPointer<Phoneme> value)
{
    if(!contains(key))
    {
        return false;
    }
    dictionary.insert(key, value);
    return true;
}

void PhonemeRepository::remove(const QString &key)
{
    if(contains(key))
    {
        dictionary.remove(key);
    }
}
