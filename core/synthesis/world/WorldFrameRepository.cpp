/* WorldFrameRepository.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "corpus/Phoneme.h"
#include "dsp/PlatinumResidualCalculator.h"
#include "dsp/StarSpectrumEstimator.h"

#include "WorldFrameRepository.h"

using namespace stand;

WorldFrameRepository::WorldFrameRepository(QSharedPointer<ResourceRepository<PhonemeKey, WaveformFrameInfoList> > waveformInfoRepository,
        QSharedPointer<ResourceRepository<QString, WorldWaveform> > waveformRepository,
        QSharedPointer<WorldFrameAnalyzer> frameAnalyzer
    ) : waveformInfoRepository(waveformInfoRepository), waveformRepository(waveformRepository), frameAnalyzer(frameAnalyzer) { }

const QSharedPointer<WorldFrame> WorldFrameRepository::find(const PhonemeKey &key) const
{
    if(waveformInfoRepository.isNull() || waveformRepository.isNull() || frameAnalyzer.isNull())
    {
        return QSharedPointer<WorldFrame>();
    }
    if(!contains(key))
    {
        return QSharedPointer<WorldFrame>();
    }

    // Get waveform.
    auto infos = (waveformInfoRepository->find(key));
    QList<QSharedPointer<WorldWaveform> > waveforms;
    foreach(const WaveformFrameInfo &info, *(infos.data()))
    {
        waveforms.append(waveformRepository->find(info.filename));
    }

    if(waveforms.empty())
    {
        return QSharedPointer<WorldFrame>();
    }

    return frameAnalyzer->analyze(key, *infos, waveforms);
}

bool WorldFrameRepository::contains(const PhonemeKey &key) const
{
    return waveformInfoRepository->contains(key);
}

bool WorldFrameRepository::add(const PhonemeKey &/*key*/, QSharedPointer<WorldFrame> /*value*/)
{
    return false;
}

void WorldFrameRepository::remove(const PhonemeKey &/*key*/)
{
    return;
}
