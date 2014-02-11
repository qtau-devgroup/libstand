/* CorpusMeta.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "CorpusMeta.h"

using namespace stand;

CorpusMeta::CorpusMeta(const QString &name, const QString &imagePath, const QString &samplePath, const QString &author, const QUrl &web) :
    name(name), imagePath(imagePath), samplePath(samplePath), author(author), web(web)
{
}

CorpusMeta::CorpusMeta(const CorpusMeta &other) :
    CorpusMeta(other.name, other.imagePath, other.samplePath, other.author, other.web)
{
}

CorpusMeta &CorpusMeta::operator =(const CorpusMeta &other)
{
    name = other.name;
    imagePath = other.imagePath;
    samplePath = other.samplePath;
    author = other.author;
    web = other.web;
    return *this;
}
