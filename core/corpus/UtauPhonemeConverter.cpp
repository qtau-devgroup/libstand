/* UtauPhonemeConverter.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include <QDir>
#include "dsp/Signal.h"

#include "UtauPhonemeConverter.h"

using namespace stand;

QSharedPointer<Phoneme> UtauPhonemeConverter::convert(
        const UtauPhoneme &utau,
        const QDir &dir,
        const QSharedPointer<ResourceFactory<QString, Signal> > signalFactory) const
{
    QString filename = dir.filePath(utau.filename);
    double msBegin = utau.msLeftBlank;
    double msFixedLength = utau.msFixedLength;
    double msPreutterance = utau.msPreutterance;
    double msOverlap = utau.msOverlap;
    double msLength = 0.0;
    // If right blank is set less than zero, the absolute value means length[msec.].
    if(utau.msRightBlank < 0)
    {
        msLength = -utau.msRightBlank;
    }
    else
    {
       auto signal(signalFactory->create(filename));
       if(signal.isEmpty())
       {
           return QSharedPointer<Phoneme>();
       }
       msLength = signal.msLength() - utau.msLeftBlank - utau.msRightBlank;
    }
    return QSharedPointer<Phoneme>(new Phoneme(filename, msBegin, msLength, msFixedLength, msPreutterance, msOverlap));
}
