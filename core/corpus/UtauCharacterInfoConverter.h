/* UtauCharacterInfoConverter.h from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#ifndef UTAUCHARACTERINFOCONVERTER_H
#define UTAUCHARACTERINFOCONVERTER_H

#include "corpus/CorpusMeta.h"
#include "utau/UtauCharacterInfo.h"

namespace stand
{

/**
 * @brief The UtauCharacterInfoConverter class converts UtauCharacterInfo into CorpusMeta.
 * @author Hal@shurabaP
 */
class UtauCharacterInfoConverter
{
public:
    virtual ~UtauCharacterInfoConverter(){ }

    virtual CorpusMeta convert(const QDir &directory, const UtauCharacterInfo &info) const;
};

}

#endif // UTAUCHARACTERINFOCONVERTER_H
