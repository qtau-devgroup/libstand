/* UtauPhonemeConverter.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef UTAUPHONEMECONVERTER_H
#define UTAUPHONEMECONVERTER_H

#include "corpus/Phoneme.h"
#include "dsp/WaveFileSignalFactory.h"
#include "utau/UtauPhoneme.h"
#include "util/ResourceRepository.h"

namespace stand
{

/**
 * @brief The UtauPhonemeConverter class converts UTAU phoneme into STAND phoneme.
 * @author Hal@shurabaP
 */
class UtauPhonemeConverter
{
public:
    virtual ~UtauPhonemeConverter(){ }

    /**
     * @brief convert converts UTAU phoneme into STAND phoneme.
     *        This method may read WAVE file if needed.
     * @param utau is a UTAU phoneme to convert.
     * @param dir is a base directory that `utau` exists in.
     * @param signalFactory
     * @return a STAND phoneme.
     */
    virtual QSharedPointer<Phoneme> convert(
        const UtauPhoneme &utau,
        const QDir &dir,
        const QSharedPointer<ResourceFactory<QString, Signal> > signalFactory
    ) const ;
};

}

#endif // UTAUPHONEMECONVERTER_H
