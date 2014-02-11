/* UtauVoicebank.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUVOICEBANK_H
#define UTAUVOICEBANK_H

#include <QDir>
#include <QHash>
#include <QSharedPointer>

#include "utau/UtauCharacterInfo.h"
#include "utau/UtauOtoHash.h"
#include "utau/UtauPrefixMap.h"

namespace stand
{

class UtauVoicebank;

/**
 * @brief The UtauVoicebankFactory class is a factory class of UtauVoicebank.
 * @author Hal@shurabaP
 */
class UtauVoicebankFactory
{
public:
    /**
     * @brief UtauVoicebankFactory is a default constructor for UtauVoicebankFactory.
     * @param recursive determines whether or not this factory reads oto.ini recursively.
     * @param otoFactory is a factory class of oto file.
     */
    explicit UtauVoicebankFactory(
        bool recursive = true,
        QSharedPointer<UtauOtoHashFactory> otoFactory = QSharedPointer<UtauOtoHashFactory>(new UtauOtoHashFactory()),
        const QString &characterFileName = "character.txt",
        const QString &prefixMapFileName = "prefix.map",
        const QString &otoIniFileName = "oto.ini",
        QTextCodec *codec = QTextCodec::codecForName("Shift-JIS")
    );
    virtual ~UtauVoicebankFactory(){ }

    /**
     * @brief create UtauVoicebank from UTAU voicebank root directory.
     * @param root to read.
     * @return UtauVoicebank.
     */
    virtual UtauVoicebank create(const QDir &root) const;
private:
    QList<UtauOtoHash> readOto(const QDir &dir, bool recursive) const;
    UtauCharacterInfo readCharacter(const QFileInfo &filepath) const;
    UtauPrefixMap readPrefixMap(const QFileInfo &filepath) const;

    bool recursive = true;
    QSharedPointer<UtauOtoHashFactory> otoFactory;
    const QString &characterFileName;
    const QString &prefixMapFileName;
    const QString &otoIniFileName;
    QTextCodec *codec;
};

/**
 * @brief The UtauVoicebank class represents UTAU voicebank.
 * @author Hal@shurabaP
 */
class UtauVoicebank
{
public:
    UtauVoicebank(const QDir &root, const UtauPrefixMap &prefixMap, const UtauCharacterInfo &info, const QList<UtauOtoHash> &otos);
    UtauVoicebank(const UtauVoicebank &other);

    virtual ~UtauVoicebank(){ }

    /**
     * @brief apply is a factory method of UtauVoicebank.
     *        This method simply delegates UtauVoicebank creation to the given factory.
     *        The default factory is a UtauVoicebankFactory.
     * @param root is a root directory of a UTAU voicebank to read.
     * @param factory to use.
     * @return UtauVoicebank.
     */
    static UtauVoicebank apply(
        const QDir &root,
        const QSharedPointer<UtauVoicebankFactory> factory = QSharedPointer<UtauVoicebankFactory>(new UtauVoicebankFactory)
    );

    /**
     * @brief isEmpty returns whether or not voicebank is empty.
     * @return true if this voicebank contains nothing, otherwise false.
     */
    bool isEmpty() const { return otos.empty(); }

    QDir root;
    UtauPrefixMap prefixMap;
    UtauCharacterInfo characterInfo;
    QList<UtauOtoHash> otos;
};

}

#endif // UTAUVOICEBANK_H
