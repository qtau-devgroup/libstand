/* PhonemeKey.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef PHONEMEKEY_H
#define PHONEMEKEY_H

#include <QString>

namespace stand
{

/**
 * @brief The PhonemeKey class is a key type for corpus.
 *        Corpus class will return result found.
 * @note operator == is not a fuzzy compare.
 * @author Hal@shurabaP
 */
class PhonemeKey
{
public:
    PhonemeKey(const QString &pronounce, double amplify, double msPosition, int velocity, int noteNumber);
    PhonemeKey(const PhonemeKey &other);

    PhonemeKey &operator =(const PhonemeKey &other);
    bool operator ==(const PhonemeKey &other) const;
    /**
     * @brief withAmplify copies this PhonemeKey with the specified amplify value.
     * @param amplify
     * @return copied PhonemeKey.
     */
    PhonemeKey withAmplify(double amplify) const;

    /**
     * @brief withAmplify copies this PhonemeKey with the msPosition value
     * @param msPosition
     * @return copied PhonemeKey.
     */
    PhonemeKey withMsPosition(double msPosition) const;

    QString pronounce;
    double amplify;
    double msPosition;
    int velocity;
    int noteNumber;
};

}

#endif // PHONEMEKEY_H
