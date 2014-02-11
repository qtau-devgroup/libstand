/* FftTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef FFTTEST_H
#define FFTTEST_H

#include <QObject>
#include "dsp/FftSg.h"
#include "AutoTest.h"

namespace stand
{

class FftTest : public QObject
{
    Q_OBJECT
private slots:
    void forward_fft_of_white_spectrum_is_single_pulse()
    {
        int fftLength = 32;
        Fft fft(fftLength, Fft::Complex);
        double *inout = new double[fftLength * 2];
        for(int i = 0; i < fftLength; i++)
        {
            inout[i * 2] = 1.0;
            inout[i * 2 + 1] = 0.0;
        }
        fft.execute(Fft::Forward, inout);
        QCOMPARE(inout[0], (double)fftLength);
        for(int i = 1; i < fftLength * 2; i++)
        {
            // qFuzzyCompare needs to add 1.0 when compare zero values.
            QCOMPARE(inout[i] + 1.0, 0.0 + 1.0);
        }
        delete[] inout;
    }

    void forward_fft_of_white_spectrum_is_single_pulse_with_real_method()
    {
        int fftLength = 32;
        Fft fft(fftLength, Fft::Real);
        double *inout = new double[fftLength];
        for(int i = 0; i < fftLength; i++)
        {
            inout[i] = 1.0;
        }
        fft.execute(Fft::Forward, inout);
        QCOMPARE(inout[0], (double)fftLength);
        for(int i = 1; i < fftLength / 2; i++)
        {
            // qFuzzyCompare needs to add 1.0 when compare zero values.
            QCOMPARE(inout[i * 2] + 1.0, 0.0 + 1.0);
            QCOMPARE(inout[i * 2  +1] + 1.0, 0.0 + 1.0);
        }
        delete[] inout;
    }
};

}

DECLARE_TEST(stand::FftTest)

#endif // FFTTEST_H
