/* UtauPrefixMap.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUPREFIXMAP_H
#define UTAUPREFIXMAP_H

#include <QString>

namespace stand
{

/**
 * @brief The UtauPrefix class represents a single element of prefix.map
 * @author Hal@shurabaP
 */
class UtauPrefix
{
public:
    UtauPrefix(const QString directory, const QString suffix) :
        directory(directory), suffix(suffix){ }

    UtauPrefix(const UtauPrefix &other) :
        UtauPrefix(other.directory, other.suffix){ }

    UtauPrefix():
        UtauPrefix("", ""){ }

    QString directory;
    QString suffix;
};

/**
 * @brief The UtauPrefixMap class represents a prefix map of UTAU voicebank.
 * @author Hal@shurabaP
 */
class UtauPrefixMap
{
public:
    explicit UtauPrefixMap(const QStringList &lines);
    UtauPrefixMap(const UtauPrefixMap &other);
    UtauPrefixMap &operator =(const UtauPrefixMap &other);

    virtual ~UtauPrefixMap(){ }

    virtual const UtauPrefix &at(int i) const;

    /**
     * @brief parse parses UtauPrefixMap from a list of string.
     * @param lines
     * @return UtauPrefixMap
     */
    static UtauPrefixMap parse(const QStringList &lines);
private:
    UtauPrefixMap(const UtauPrefix *prefix);
    UtauPrefix prefix[127];
};

}

#endif // UTAUPREFIXMAP_H
