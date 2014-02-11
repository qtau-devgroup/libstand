/* DecimatorTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef DECIMATORTEST_H
#define DECIMATORTEST_H

#include <QObject>
#include "dsp/Signal.h"
#include "dsp/Decimator.h"
#include "helpers/WorldDecimator.h"

#include "AutoTest.h"

namespace stand
{

class DecimatorTest : public QObject
{
    Q_OBJECT
private slots:
    void decimate_equals_to_pre_calculated_values()
    {
        int length = 44101;
        Signal signal(length, length);
        double *doubleWave = new double[length];
        for(int i = 0; i < length; i++)
        {
            doubleWave[i] = signal[i] = (double)rand() / RAND_MAX;
        }
        for(int r = 1; r < 12; r++)
        {
            int decimatedLength = 1 + length / r;
            double *expected = new double[decimatedLength];
            double *actual = new double[decimatedLength];
            WorldDecimator::decimate(doubleWave, length, r, expected, decimatedLength);
            Decimator::decimate(signal, r, actual, decimatedLength);
            for(int i = 0; i < decimatedLength; i++)
            {
                QCOMPARE(actual[i], expected[i]);
            }
            delete[] expected;
            delete[] actual;
        }
        delete[] doubleWave;
    }
};

}

DECLARE_TEST(stand::DecimatorTest)

#endif // DECIMATORTEST_H
