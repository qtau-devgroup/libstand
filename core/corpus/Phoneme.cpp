/* Phoneme.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "Phoneme.h"

using namespace stand;

Phoneme::Phoneme(const QString &filename, double msLeftBlank, double msLength, double msFixedLength, double msPreutterance, double msOverlap) :
    filename(filename), msBegin(msLeftBlank), msLength(msLength), msFixedLength(msFixedLength), msPreutterance(msPreutterance), msOverlap(msOverlap)
{
}

Phoneme::Phoneme(const Phoneme &other) :
    Phoneme(other.filename, other.msBegin, other.msLength, other.msFixedLength, other.msPreutterance, other.msOverlap)
{
}

Phoneme &Phoneme::operator =(const Phoneme &other)
{
    this->filename = other.filename;
    this->msBegin = other.msBegin;
    this->msLength = other.msLength;
    this->msFixedLength = other.msFixedLength;
    this->msPreutterance = other.msPreutterance;
    this->msOverlap = other.msOverlap;
    return *this;
}

bool Phoneme::operator ==(const Phoneme &other) const
{
    return this->filename == other.filename &&
            this->msBegin == other.msBegin &&
            this->msLength == other.msLength &&
            this->msFixedLength == other.msFixedLength &&
            this->msPreutterance == other.msPreutterance &&
            this->msOverlap == other.msOverlap;
}
