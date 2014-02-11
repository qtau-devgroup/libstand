/* StarSpectrumEstimatorTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef STARSPECTRUMESTIMATORTEST_H
#define STARSPECTRUMESTIMATORTEST_H

#include "dsp/Signal.h"
#include "dsp/StarSpectrumEstimator.h"
#include "dsp/world/dio.h"
#include "dsp/world/star.h"
#include "AutoTest.h"
#include <time.h>
#include <qmath.h>
#include <float.h>
#include <QTest>
#include <QObject>

namespace stand
{

const double Error = 0.01;

class StarSpectrumEstimatorTest : public QObject
{
    Q_OBJECT
private slots:
    void StarSpectrumEstimator_estimate_should_return_the_same_value_as_original_star()
    {
        const int fs = 44100;
        const int length = 44100;
        const double msFramePeriod = 2.0;
        const int tLen = GetSamplesForDIO(fs, length, msFramePeriod);
        const int fftLength = GetFFTSizeForStar(fs);
        double *dWave = new double[length];
        Signal fWave(length, fs);
        double *f0 = new double[tLen];
        double *t = new double[tLen];
        double **expect = new double *[tLen];
        expect[0] = new double[tLen * fftLength];
        for(int i = 1; i < tLen; i++)
        {
            expect[i] = expect[0] + i * fftLength;
        }
        QList<QSharedPointer<double> > actual;
        actual.reserve(tLen);
        for(int i = 0; i < length; i++)
        {
            dWave[i] = fWave[i] = (i % 100 == 0) ? 1.0 : 0.0;
        }
        for(int i = 0; i < tLen; i++)
        {
            f0[i] = (float)f0[i];
        }
        Dio(dWave, length, fs, msFramePeriod, t, f0);
        clock_t begin;
        begin = clock();
        Star(dWave, length, fs, t, f0, tLen, expect);
        printf("OriginalStar ElapsedTime : %lf[sec]\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
        StarSpectrumEstimator estimator(fftLength);
        begin = clock();
        for(int i = 0; i < tLen ; i++)
        {
            actual.append(estimator.estimate(fWave, i * msFramePeriod, f0[i]));
        }
        printf("StarSpectrumEstimator ElapsedTime : %lf[sec]\n", (double)(clock() - begin) / CLOCKS_PER_SEC);

        for(int i = 0; i < tLen ; i++)
        {
            for(int j = 0; j <= fftLength / 2; j++)
            {
                double error = fabs(1.0 - (1.0 + actual[i].data()[j]) / (1.0 + expect[i][j]));
                if(error > Error)
                {
                    printf("actual = %e while expected = %e at (i = %d, j = %d)\n", actual[i].data()[j], expect[i][j], i, j);
                    QFAIL("Error is too big.");
                }
            }
        }

        delete[] expect[0];
        delete[] expect;
        delete[] dWave;
        delete[] f0;
        delete[] t;
    }
};

}

DECLARE_TEST(stand::StarSpectrumEstimatorTest)

#endif // STARSPECTRUMESTIMATORTEST_H
