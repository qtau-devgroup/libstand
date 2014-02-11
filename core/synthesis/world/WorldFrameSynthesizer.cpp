/* WorldFrameSynthesizer.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include "dsp/FftSg.h"
#include "dsp/MinimumPhase.h"
#include "dsp/Signal.h"

#include "WorldFrameSynthesizer.h"

using namespace stand;

double WorldFrameSynthesizer::synthesize(Signal &dst, const QSharedPointer<WorldFrame> &src, double ms)
{
    if(src.isNull())
    {
        return 0.0;
    }

    // Get minimum phase spectrum of src->spectrum.
    MinimumPhase minimum(src->fftLength);
    Fft fft(src->fftLength, Fft::Real);
    QSharedPointer<double> minimumPhase(minimum.execute(src->spectrum));

    // Calculate spectrum from minimum-phase and PLATINUM residual.
    double *d = minimumPhase.data();
    double *residual = src->residual.data();

    for(int i = 1; i < src->fftLength / 2; i++)
    {
        double re = d[i * 2];
        double im = d[i * 2 + 1];
        d[i * 2] = re * residual[i * 2] - im * residual[i * 2 + 1];
        d[i * 2 + 1] = re * residual[i * 2 + 1] + im * residual[i * 2];
    }
    d[0] = d[0] * residual[0];
    d[1] = d[src->fftLength] * residual[1];

    // Get waveform.
    fft.execute(Fft::Inverse, d);

    // Add to buffer.
    int begin = ms / 1000.0 * dst.samplingFrequency();
    int end = qMin(begin + src->fftLength, dst.length());
    int size = src->fftLength / 2;
    for(int i = begin, j = 0; i < end; i++, j++)
    {
        dst[i] += d[j] / size;
    }
    return src->f0;
}
