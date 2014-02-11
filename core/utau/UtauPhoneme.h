/* UtauPhoneme.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUPHONEME_H
#define UTAUPHONEME_H

#include <QString>

namespace stand
{

/**
 * @brief The UtauPhoneme class represents a single UTAU phoneme in oto.ini.
 * @author Hal@shurabaP
 */
class UtauPhoneme
{
public:
    /**
     * @brief UtauPhoneme is a single line in UTAU oto.ini.
     * @param pronounce is an alias in oto.ini.
     * @param filename is a filename corresponding to this UtauPhoneme instance.
     * @param msLeftBlank means how long the file contains a blank data at its head.
     * @param msFixedLength means how long the file contains unextendable data after msLeftBlank.
     * @param msRightBlank means how long the file contains a blank data at its tail.
     * @param msPreutterance means how long the phoneme should be located before the proper timing.
     * @param msOverlap means how long the phoneme should be overlapped to the previous phoneme.
     */
    UtauPhoneme(const QString &pronounce,
                const QString &filename,
                double msLeftBlank,
                double msFixedLength,
                double msRightBlank,
                double msPreutterance,
                double msOverlap);
    /**
     * @brief UtauPhoneme is a copy constructor.
     * @param that will be copied to this instance.
     */
    UtauPhoneme(const UtauPhoneme &that);
    virtual ~UtauPhoneme(){}

    bool operator ==(const UtauPhoneme &that) const;

    /**
     * @brief copy creates a copied instance of this.
     * @return copied instance.
     */
    UtauPhoneme copy() const;

    QString pronounce;
    QString filename;

    double msLeftBlank;
    double msFixedLength;
    double msRightBlank;
    double msPreutterance;
    double msOverlap;
};

}

#endif // UTAUPHONEME_H
