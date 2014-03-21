/* UtauCharacterInfoConverter.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include <QDir>

#include "UtauCharacterInfoConverter.h"

using namespace stand;

CorpusMeta UtauCharacterInfoConverter::convert(const QDir &directory, const UtauCharacterInfo &info) const
{
    return CorpusMeta(
                info.name,
                directory.relativeFilePath(info.image.absoluteFilePath()),
                directory.relativeFilePath(info.sample.absoluteFilePath()),
                info.author,
                info.web);
}
