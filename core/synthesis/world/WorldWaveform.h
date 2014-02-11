/* WorldWaveform.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDWAVEFORM_H
#define WORLDWAVEFORM_H

#include <QList>

#include "dsp/Contour.h"
#include "dsp/Signal.h"

namespace stand
{

/**
 * @brief The WorldWaveform class is a waveform class for WORLD analysis and synthesis.
 *        WorldWaveform contains signal, its f0 contour and its peak indices fot TD-PSOLA.
 *        And also this class contains frame period [msec] as msFramePeriod.
 *        msFramePeriod is length for a single index for f0 contour and peka indices.
 * @author Hal@shurabaP
 */
class WorldWaveform
{
public:
    WorldWaveform(const Signal &signal = Signal(),
                  const Contour<float> &f0Contour = Contour<float>(),
                  const Contour<int> &peakIndices = Contour<int>(),
                  double msFramePeriod = 1.0);

    WorldWaveform(const WorldWaveform &other);
    WorldWaveform &operator =(const WorldWaveform &other);

    Signal signal;
    Contour<float> f0Contour;
    Contour<int> peakIndices;
    double msFramePeriod;
};

}

#endif // WORLDWAVEFORM_H
