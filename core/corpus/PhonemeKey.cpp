/* PhonemeKey.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "PhonemeKey.h"

using namespace stand;

PhonemeKey::PhonemeKey(const QString &pronounce, double amplify, double msPosition, int velocity, int noteNumber) :
    pronounce(pronounce), amplify(amplify), msPosition(msPosition), velocity(velocity), noteNumber(noteNumber)
{
}

PhonemeKey::PhonemeKey(const PhonemeKey &other) :
    PhonemeKey(other.pronounce, other.amplify, other.msPosition, other.velocity, other.noteNumber)
{
}

PhonemeKey &PhonemeKey::operator =(const PhonemeKey &other)
{
    this->pronounce = other.pronounce;
    this->amplify = other.amplify;
    this->noteNumber = other.noteNumber;
    this->msPosition = other.msPosition;
    this->velocity = other.velocity;

    return *this;
}

bool PhonemeKey::operator ==(const PhonemeKey &other) const
{
    return this->pronounce == other.pronounce &&
            this->amplify == other.amplify &&
            this->msPosition == other.msPosition &&
            this->velocity == other.velocity &&
            this->noteNumber == other.noteNumber;
}

PhonemeKey PhonemeKey::withAmplify(double amplify) const
{
    PhonemeKey result(*this);
    result.amplify = amplify;
    return result;
}

PhonemeKey PhonemeKey::withMsPosition(double msPosition) const
{
    PhonemeKey result(*this);
    result.msPosition = msPosition;
    return result;
}
