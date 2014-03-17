/* WaveformCorpus.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QJsonObject>

#include "corpus/PhonemeRepository.h"
#include "WaveformCorpus.h"

using namespace stand;

WaveformCorpus::WaveformCorpus(
    const CorpusMeta &meta,
    const QSharedPointer<NotePhonemeMapper> phonemeMapper,
    const QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories,
    const QSharedPointer<PhonemeSelector> selector
) : meta(meta), phonemeMapper(phonemeMapper), phonemeRepositories(phonemeRepositories), selector(selector)
{
}

WaveformCorpus::WaveformCorpus(const WaveformCorpus &other) :
    WaveformCorpus(other.meta, other.phonemeMapper, other.phonemeRepositories, other.selector)
{
}

const QSharedPointer<WaveformFrameInfoList> WaveformCorpus::find(const PhonemeKey &key) const
{
    if(!contains(key))
    {
        return QSharedPointer<WaveformFrameInfoList>();
    }
    // contain should ensure that all ids in items should exist in phonemeRepositories.
    const NotePhonemeMappingList &items = phonemeMapper->find(key.noteNumber, key.velocity);
    QList<QSharedPointer<Phoneme> > phonemes;
    foreach(const auto &item, items)
    {
        phonemes.append(phonemeRepositories[item.id]->find(key.pronounce));
    }
    return selector->select(key.msPosition, items, phonemes);
}

bool WaveformCorpus::contains(const PhonemeKey &key) const
{
    const auto &items = phonemeMapper->find(key.noteNumber, key.velocity);
    bool result = true;
    foreach(const auto &item, items)
    {
        result &= phonemeRepositories.contains(item.id);
    }
    result &= !items.empty();
    return result;
}

bool WaveformCorpus::add(const PhonemeKey &/*key*/, QSharedPointer<WaveformFrameInfoList> /*value*/)
{
    return false;
}

void WaveformCorpus::remove(const PhonemeKey &/*key*/)
{
}

QJsonValue WaveformCorpus::toJson() const
{
    QJsonObject object;
    object["meta"] = meta.toJson();
    object["mapper"] = phonemeMapper->toJson();
    QJsonObject repositories;
    foreach(const QString &key, phonemeRepositories.keys())
    {
        const PhonemeRepository *repository = dynamic_cast<const PhonemeRepository *>(phonemeRepositories[key].data());
        if(repository == NULL)
        {
            continue;
        }
        repositories["key"] = repository->toJson();
    }
    object["phonemes"] = repositories;

    return QJsonValue(object);
}

QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > WaveformCorpus::fromJson(
        const QJsonValue &json,
        const QSharedPointer<PhonemeSelector> selector)
{
    if(!json.isObject())
    {
        return QSharedPointer<WaveformCorpus>();
    }
    const QJsonObject object(json.toObject());
    if(!object["phonemes"].isObject())
    {
        return QSharedPointer<WaveformCorpus>();
    }

    QSharedPointer<CorpusMeta> meta(CorpusMeta::fromJson(object["meta"]));
    QSharedPointer<NotePhonemeMapper> phonemeMapper(NotePhonemeMapper::fromJson(object["mapper"]));
    QHash<QString, QSharedPointer<ResourceRepository<QString, Phoneme> > > phonemeRepositories;
    QJsonObject repositories(object["phonemes"].toObject());

    for(auto it = repositories.constBegin(); it != repositories.constEnd(); it++)
    {
        QSharedPointer<ResourceRepository<QString, Phoneme> > repository(PhonemeRepository::fromJson(it.value()));
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

    return QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> >(
            new WaveformCorpus(*meta, phonemeMapper, phonemeRepositories, selector)
            );
}
