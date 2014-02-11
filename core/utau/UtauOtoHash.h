/* UtauOtoHash.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef UTAUOTOHASH_H
#define UTAUOTOHASH_H

#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QSharedPointer>
#include <QTextCodec>

#include "utau/UtauPhoneme.h"

namespace stand
{
class UtauOtoHash;

/**
 * @brief The UtauOtoHashFactory class is a factory class of UtauOtoHash.
 * @author Hal@shurabaP
 */
class UtauOtoHashFactory
{
public:
    /**
     * @brief UtauOtoHashFactory creates OtoHashFactory from text-codec.
     * @param codec is a text-codec. The default value is set to `Shift-JIS`
     */
    explicit UtauOtoHashFactory(QTextCodec *codec = QTextCodec::codecForName("Shift-JIS"));
    /**
     * @brief UtauOtoHashFactory is a copy constructor.
     * @param other will be copied to this instance.
     */
    UtauOtoHashFactory(const UtauOtoHashFactory &other);
    /**
     * @brief operator = copies OtoHashFactory.
     * @param other will be copied to this instance.
     * @return copied OtoHashFactory.
     */
    UtauOtoHashFactory &operator =(const UtauOtoHashFactory &other);

    virtual ~UtauOtoHashFactory(){}

    /**
     * @brief read oto.ini file and create UtauOtoHash.
     *        If file contains an invalid line, the line will be ignored.
     * @param fileinfo is a file path of oto.ini.
     * @return UtauOtoHash.
     */
    virtual UtauOtoHash read(const QFileInfo &fileinfo) const;
    /**
     * @brief read oto.ini content and create UtauOtoHash.
     *        If read failed to parse a line, the line will be ignored.
     * @param otoList is a file content.
     * @param dir is a directory of oto.ini.
     * @return UtauOtoHash.
     */
    virtual UtauOtoHash parse(const QList<QString> &otoList, const QDir &dir = QDir()) const;
protected:
    QTextCodec *textCodec;
};

/**
 * @brief The UtauOtoHash class represents UTAU oto.ini.
 *        This class extends QHash<QString, UtauPhoneme> and contains directory-value of oto.ini.
 * @author Hal@shurabaP
 */
class UtauOtoHash : public QHash<QString, UtauPhoneme>
{
public:
    /**
     * @brief UtauOtoHash is a simple constructor. The object will be initialized as an empty one.
     */
    UtauOtoHash();
    /**
     * @brief UtauOtoHash is a constructor which reads the oto.ini from fileinfo.
     *        When reading the file is failed, OtoHash will be an empty one.
     * @param fileinfo is a filepath to oto.ini.
     * @param codec is a character codec. Default codec is set to `Shift-JIS`.
     */
    explicit UtauOtoHash(const QFileInfo &fileinfo, QTextCodec *codec = QTextCodec::codecForName("Shift-JIS"));
    /**
     * @brief UtauOtoHash is a copy constructor.
     * @param other will be copied to the instance.
     */
    UtauOtoHash(const UtauOtoHash &other);

    virtual ~UtauOtoHash(){ }

    /**
     * @brief setDirectory sets a directory path of oto.ini.
     * @param dir the directory of oto.ini.
     */
    void setDirectory(const QDir dir);
    /**
     * @brief directory is a directory path of oto.ini.
     * @return a directory path.
     */
    const QDir &directory() const;

    /**
     * @brief apply is a factory method of UtauOtoHash.
     *        This method simply delegates UatuOtoHash creation to the given factory.
     *        The default factory is a UtauOtoHashFactory with Shift-JIS codec.
     * @param filepath to read.
     * @param factory to use.
     * @return UtauOtoHash.
     */
    static UtauOtoHash apply(
        const QFileInfo &filepath,
        const QSharedPointer<UtauOtoHashFactory> factory = QSharedPointer<UtauOtoHashFactory>(new UtauOtoHashFactory())
    );
protected:
    QDir dir;
};

}

#endif // UTAUOTOHASH_H
