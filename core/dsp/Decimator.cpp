/* Decimator.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <QtGlobal>
#include "Decimator.h"

#include "dsp/Signal.h"

using namespace stand;

// From WORLD : http://www.slp.is.ritsumei.ac.jp/~morise/world/
void Decimator::filter(double *inout, int length, int ratio)
{
    ratio = qMax(1, qMin(ratio, 12));
    const static double coefficient[][5] = {
        {0, 0, 0, 0, 0}, // 0
        {0, 0, 0, 0, 0}, // 1
        {0.041156734567757189, -0.42599112459189636, 0.041037215479961225, 0.16797464681802227, 0.50392394045406674},
        {0.95039378983237421, -0.67429146741526791, 0.15412211621346475, 0.071221945171178636, 0.21366583551353591},
        {1.4499664446880227, -0.98943497080950582, 0.24578252340690215, 0.036710750339322612, 0.11013225101796784},
        {1.7610939654280557, -1.2554914843859768, 0.3237186507788215, 0.021334858522387423, 0.06400457556716227},
        {1.9715352749512141, -1.4686795689225347, 0.3893908434965701, 0.013469181309343825, 0.040407543928031475},
        {2.1225239019534703, -1.6395144861046302, 0.44469707800587366, 0.0090366882681608418, 0.027110064804482525},
        {2.2357462340187593, -1.7780899984041358, 0.49152555365968692, 0.0063522763407111993, 0.019056829022133598},
        {2.3236003491759578, -1.8921545617463598, 0.53148928133729068, 0.0046331164041389372, 0.013899349212416812},
        {2.3936475118069387, -1.9873904075111861, 0.5658879979027055, 0.0034818622251927556, 0.010445586675578267},
        {2.450743295230728, -2.06794904601978, 0.59574774438332101, 0.0026822508007163792, 0.0080467524021491377},
        {2.4981398605924205, -2.1368928194784025, 0.62187513816221485, 0.0021097275904709001, 0.0063291827714127002}
    };

    // Filtering on time domain.
    double w[3] = {0.0, 0.0, 0.0};
    double wt;
    for (int i = 0; i < length; ++i)
    {
      wt = inout[i] + coefficient[ratio][0] * w[0] + coefficient[ratio][1] * w[1] + coefficient[ratio][2] * w[2];
      inout[i] = coefficient[ratio][3] * wt + coefficient[ratio][4] * w[0] + coefficient[ratio][4] * w[1] + coefficient[ratio][3] * w[2];
      w[2] = w[1];
      w[1] = w[0];
      w[0] = wt;
    }
}

// From WORLD : http://www.slp.is.ritsumei.ac.jp/~morise/world/
void Decimator::decimate(const Signal& src, int ratio, double *dst, int dstLength)
{
    const int extCount = 9;
    int srcLength = src.size();
    int extendedLength = srcLength + extCount * 2;
    double *extended = new double[extendedLength];

    for (int i = 0; i < extCount; i++)
    {
        extended[i] = 2 * src[0] - src[extCount - i];
    }
    for (int i = extCount; i < extCount + srcLength; i++)
    {
        extended[i] = src[i - extCount];
    }
    for (int i = extCount + srcLength; i < extendedLength; i++)
    {
        extended[i] = 2 * src[srcLength - 1] - src[srcLength - 2 - (i - (extCount + srcLength))];
    }

    filter(extended, extendedLength, ratio);
    for (int i = 0; i < extendedLength / 2; i++)
    {
        double tmp = extended[i];
        extended[i] = extended[extendedLength - i - 1];
        extended[extendedLength - i - 1] = tmp;
    }
    filter(extended, extendedLength, ratio);
    for (int i = 0; i < extendedLength / 2; i++)
    {
        double tmp = extended[i];
        extended[i] = extended[extendedLength - i - 1];
        extended[extendedLength - i - 1] = tmp;
    }
    int outLength = srcLength / ratio + 1;
    int offset = ratio - ratio * outLength + srcLength;

    for (int i = offset, index = 0; i < srcLength + extCount && index < dstLength; i += ratio, index++)
    {
        dst[index] = extended[i + extCount - 1];
    }

    delete[] extended;
}

