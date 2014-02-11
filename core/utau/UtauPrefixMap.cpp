/* UtauPrefixMap.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QStringList>

#include "util/MusicalNote.h"
#include "UtauPrefixMap.h"

using namespace stand;

UtauPrefixMap::UtauPrefixMap(const QStringList &lines) :
    UtauPrefixMap(parse(lines))
{
}

UtauPrefixMap::UtauPrefixMap(const UtauPrefixMap &other) :
    UtauPrefixMap(other.prefix)
{
}

UtauPrefixMap::UtauPrefixMap(const UtauPrefix *prefix)
{
    for(int i = 0; i < 127; i++)
    {
        this->prefix[i] = prefix[i];
    }
}

UtauPrefixMap &UtauPrefixMap::operator =(const UtauPrefixMap &other)
{
    for(int i = 0; i < 127; i++)
    {
        this->prefix[i] = other.prefix[i];
    }
    return *this;
}

UtauPrefixMap UtauPrefixMap::parse(const QStringList &lines)
{
    UtauPrefix prefixes[127];
    foreach(const QString &line, lines)
    {
        QStringList params(line.split("\t"));
        if(params.size() != 3)
        {
            continue;
        }
        int note = MusicalNote::noteNumber(params[0]);
        if(note < 0 || 127 <= note)
        {
            continue;
        }
        prefixes[note] = UtauPrefix(params[1], params[2]);
    }
    return UtauPrefixMap(prefixes);
}

const UtauPrefix &UtauPrefixMap::at(int i) const
{
    int index = qMax(0, qMin(126, i));
    return prefix[index];
}
