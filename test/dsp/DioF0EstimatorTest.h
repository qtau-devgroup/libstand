/* DioF0EstimatorTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef DIOF0ESTIMATORTEST_H
#define DIOF0ESTIMATORTEST_H

#include "dsp/Signal.h"
#include "dsp/DioF0Estimator.h"
#include "dsp/world/dio.h"
#include "AutoTest.h"
#include <qmath.h>
#include <time.h>
#include <QObject>

namespace stand
{

class DioF0EstimatorTest : public QObject
{
    Q_OBJECT
private slots:
    void result_of_estimation_should_be_equal_to_dio()
    {
        const int fs = 44100;
        const int length = 44100 * 10;
        const double msFramePeriod = 2.0;
        const int tLen = GetSamplesForDIO(fs, length, msFramePeriod);
        double *dWave = new double[length];
        Signal signal(length, fs);
        double *expect = new double[tLen];
        double *t = new double[tLen];
        for(int i = 0; i < length; i++)
        {
            dWave[i] = signal[i] = sin(2 * M_PI * i / 100.0);
        }
        clock_t begin;
        begin = clock();
        QList<float> actual(DioF0Estimator().estimate(signal, msFramePeriod);
        printf("DioF0Estimator ElapsedTime : %lf[sec]\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
        begin = clock();
        Dio(dWave, length, fs, msFramePeriod, t, expect);
        printf("OriginalDio ElapsedTime : %lf[sec]\n", (double)(clock() - begin) / CLOCKS_PER_SEC);

        QCOMPARE(actual.size(), tLen);
        for(int i = 0; i < tLen; i++)
        {
            QCOMPARE(actual[i], signal[i]);
        }
        delete[] dWave;
        delete[] fWave;
        delete[] expect;
        delete[] t;
    }
};

}

DECLARE_TEST(stand::DioF0EstimatorTest)

#endif // DIOF0ESTIMATORTEST_H
