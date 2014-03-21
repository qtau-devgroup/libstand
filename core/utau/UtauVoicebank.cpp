/* UtauVoicebank.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QTextStream>

#include "UtauVoicebank.h"

using namespace stand;

namespace
{
QStringList readAllLines(QTextStream *stream)
{
    QStringList lines;
    while(!stream->atEnd())
    {
        lines.append(stream->readLine());
    }
    return lines;
}

}

UtauVoicebank::UtauVoicebank(const QDir &root, const UtauPrefixMap &prefixMap, const UtauCharacterInfo &info, const QList<UtauOtoHash> &otos) :
    root(root), prefixMap(prefixMap), characterInfo(info), otos(otos)
{
}

UtauVoicebank::UtauVoicebank(const UtauVoicebank &other) :
    UtauVoicebank(other.root, other.prefixMap, other.characterInfo, other.otos)
{
}

UtauVoicebank UtauVoicebank::apply(const QDir& root, QSharedPointer<UtauVoicebankFactory> factory)
{
    return factory->create(root);
}

UtauVoicebankFactory::UtauVoicebankFactory(QSharedPointer<UtauOtoHashFactory> otoFactory,
    const QString &characterFileName,
    const QString &prefixMapFileName,
    const QString &otoIniFileName,
    QTextCodec *codec
) : otoFactory(otoFactory), characterFileName(characterFileName), prefixMapFileName(prefixMapFileName), otoIniFileName(otoIniFileName), codec(codec)
{
}

UtauVoicebank UtauVoicebankFactory::create(const QDir &root) const
{
    QList<UtauOtoHash> otos(readOto(root, true));
    UtauCharacterInfo characterInfo(readCharacter(root.filePath(characterFileName)));
    UtauPrefixMap prefixMap(readPrefixMap(root.filePath(prefixMapFileName)));
    UtauVoicebank voicebank(root, prefixMap, characterInfo, otos);
    return voicebank;
}

QList<UtauOtoHash> UtauVoicebankFactory::readOto(const QDir &dir, bool subdirs) const
{
    QList<UtauOtoHash> result;
    if(subdirs)
    {
        QFileInfoList files = dir.entryInfoList(QDir::Dirs);
        foreach(const QFileInfo &dir, files)
        {
            // read just subdirectories, not recursively.
            result += readOto(dir.dir(), false);
        }
    }
    UtauOtoHash oto(otoFactory->read(dir.filePath(otoIniFileName)));
    if(!oto.empty())
    {
        result.append(oto);
    }
    return result;
}

UtauCharacterInfo UtauVoicebankFactory::readCharacter(const QFileInfo &filepath) const
{
    QFile file(filepath.absoluteFilePath());
    if(!file.open(QIODevice::ReadOnly))
    {
        return UtauCharacterInfo::parse(QStringList());
    }
    QTextStream stream(&file);
    return UtauCharacterInfo::parse(readAllLines(&stream));
}

UtauPrefixMap UtauVoicebankFactory::readPrefixMap(const QFileInfo &filepath) const
{
    QFile file(filepath.absoluteFilePath());
    if(!file.open(QIODevice::ReadOnly))
    {
        return UtauPrefixMap::parse(QStringList());
    }
    QTextStream stream(&file);
    return UtauPrefixMap::parse(readAllLines(&stream));
}
