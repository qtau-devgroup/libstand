/* WorldFrameAnalyzer.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAMEANALYZER_H
#define WORLDFRAMEANALYZER_H

#include <QSharedPointer>

#include "corpus/PhonemeKey.h"
#include "corpus/WaveformFrameInfoList.h"
#include "dsp/StarSpectrumEstimator.h"
#include "dsp/PlatinumResidualCalculator.h"
#include "synthesis/world/WorldFrame.h"
#include "synthesis/world/WorldWaveform.h"
#include "util/ResourceRepository.h"

namespace stand
{
/**
 * @brief The WorldFrameAnalyzer class is a one frame analyzer for WorldFrame.
 *        This class analyzes given waveforms at the time of key parameter,
 *        and then sums up them all and return value.
 *        Basically this class is used from WorldFrameRepository.
 * @author Hal@shurabaP
 */
class WorldFrameAnalyzer
{
public:
    virtual ~WorldFrameAnalyzer(){ }
    virtual QSharedPointer<WorldFrame> analyze(const PhonemeKey &key,
        const WaveformFrameInfoList &infos,
        const QList<QSharedPointer<WorldWaveform> > &waveforms
    );

protected:
    // for unit test.
    virtual QSharedPointer<StarSpectrumEstimator> star(int fftLength);
    // for unit test.
    virtual QSharedPointer<PlatinumResidualCalculator> platinum(int fftLength);
private:
    static int fftLengthFor(int samplingFrequency);
};

}

#endif // WORLDFRAMEANALYZER_H
