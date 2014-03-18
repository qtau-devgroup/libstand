/* QJsonWaveformCorpus.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@shurabaP, BSD license */
#include <QJsonObject>
#include "corpus/PhonemeRepository.h"
#include "corpus/PhonemeSelector.h"
#include "corpus/WaveformCorpus.h"
#include "corpus/json/QJsonCorpusMeta.h"
#include "corpus/json/QJsonNotePhonemeMapper.h"
#include "corpus/json/QJsonPhonemeRepository.h"

#include "QJsonWaveformCorpus.h"

using namespace stand;

QJsonValue stand::operator <<(QJsonValue &left, const WaveformCorpus &right)
{
    QJsonObject object;
    QJsonValue meta, mapper;
    meta << right.meta;
    mapper << *(right.phonemeMapper);
    object["meta"] = meta;
    object["mapper"] = mapper;
    QJsonObject repositories;
    foreach(const QString &key, right.phonemeRepositories.keys())
    {
        const PhonemeRepository *repository = dynamic_cast<const PhonemeRepository *>(right.phonemeRepositories[key].data());
        if(repository == NULL)
        {
            continue;
        }
        QJsonValue repos;
        repos << *repository;
        repositories["key"] = repos;
    }
    object["phonemes"] = repositories;

    return (left = QJsonValue(object));
}

QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > stand::operator >>(
        const QJsonValue &left, QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > &right)
{
    if(!left.isObject())
    {
        return QSharedPointer<WaveformCorpus>();
    }
    const QJsonObject object(left.toObject());
    if(!object["phonemes"].isObject())
    {
        return QSharedPointer<WaveformCorpus>();
    }

    QSharedPointer<CorpusMeta> meta;
    QSharedPointer<NotePhonemeMapper> phonemeMapper;
    object["meta"] >> meta;
    object["mapper"] >> phonemeMapper;

    QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
    QJsonObject repositories(object["phonemes"].toObject());

    for(auto it = repositories.constBegin(); it != repositories.constEnd(); it++)
    {
        QSharedPointer<ResourceRepository<QString, Phoneme> > repository;
        it.value() >> repository;
        if(repository.isNull())
        {
            continue;
        }
        phonemeRepositories.insert(it.key(), repository);
    }

    if(meta.isNull() || phonemeMapper.isNull() || phonemeRepositories.empty())
    {
        return QSharedPointer<WaveformCorpus>();
    }

    return (right = QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> >(
            new WaveformCorpus(*meta, phonemeMapper, phonemeRepositories)));
}
