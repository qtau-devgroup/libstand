/* PlatinumResidualCalculatorTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef PLATINUMRESIDUALCALCULATORTEST_H
#define PLATINUMRESIDUALCALCULATORTEST_H

#include <QObject>
#include <time.h>
#include "dsp/PlatinumResidualCalculator.h"
#include "dsp/Signal.h"
#include "dsp/world/common.h"
#include "dsp/world/constant_numbers.h"
#include "dsp/world/matlabfunctions.h"
#include "dsp/world/platinum.h"

#include "AutoTest.h"

namespace stand
{

class PlatinumResidualCalculatorTest : public QObject
{
    Q_OBJECT
private:
    void GetOneFrameResidualSpec(double *x, int x_length, double current_t0, ForwardRealFFT *forward_real_fft,
        MinimumPhaseAnalysis *minimum_phase, const double *spectrum, int index, int fft_size, double *residual_spectrum) {
        for (int i = 0; i <= fft_size / 2; i++) {
            minimum_phase->log_spectrum[i] = log(spectrum[i]) / 2.0;
        }
        GetMinimumPhaseSpectrum(minimum_phase);

        int window_length = matlab_round(current_t0 * 2.0);
        if (window_length + index - matlab_round(current_t0) >= x_length) {
            for (int i = 0; i < minimum_phase->fft_size; ++i)
                residual_spectrum[i] = randn() * world::kMySafeGuardMinimum;
            return;
        }

        // Windowing and FFT
        for (int i = 0; i < window_length; ++i)
            forward_real_fft->waveform[i] = x[MyMin(x_length - 1, MyMax(0, i + index - matlab_round(current_t0)))] *
                (0.5 - 0.5 * cos(2.0 * world::kPi * (i + 1.0) / (window_length + 1.0)));
        for (int i = window_length; i < minimum_phase->fft_size; ++i)
            forward_real_fft->waveform[i] = 0.0;
        fft_execute(forward_real_fft->forward_fft);

        // Convolution
        residual_spectrum[0] = forward_real_fft->spectrum[0][0] / minimum_phase->minimum_phase_spectrum[0][0];
        double tmp;
        for (int i = 0; i < minimum_phase->fft_size / 2 - 1; ++i) {
            tmp = minimum_phase->minimum_phase_spectrum[i + 1][0] * minimum_phase->minimum_phase_spectrum[i + 1][0] +
                minimum_phase->minimum_phase_spectrum[i + 1][1] * minimum_phase->minimum_phase_spectrum[i + 1][1];
            residual_spectrum[i * 2 + 1] = (minimum_phase->minimum_phase_spectrum[i + 1][0] * forward_real_fft->spectrum[i + 1][0] +
                minimum_phase->minimum_phase_spectrum[i + 1][1] * forward_real_fft->spectrum[i + 1][1]) / tmp;
            residual_spectrum[i * 2 + 2] = (-minimum_phase->minimum_phase_spectrum[i + 1][1] * forward_real_fft->spectrum[i + 1][0] +
                minimum_phase->minimum_phase_spectrum[i + 1][0] * forward_real_fft->spectrum[i + 1][1]) / tmp;
        }
        residual_spectrum[minimum_phase->fft_size - 1] =
            forward_real_fft->spectrum[minimum_phase->fft_size / 2][0] /
            minimum_phase->minimum_phase_spectrum[minimum_phase->fft_size / 2][0];
    }
private slots:
    void calculate_should_return_the_same_value_as_GetOneFrameResidualSpec()
    {
        int fftLength = 2048;
        int waveLength = 44100;
        int fs = 44100;
        double f0 = 441;
        int amount = 1;
        MinimumPhaseAnalysis ma;
        InitializeMinimumPhaseAnalysis(fftLength, &ma);
        ForwardRealFFT forward;
        InitializeForwardRealFFT(fftLength, &forward);
        double *power = new double[fftLength];
        double *dWave = new double[waveLength];
        Signal fWave(waveLength, fs);
        double *expect = new double[waveLength];
        for(int i = 0; i < waveLength; i++)
        {
            dWave[i] = fWave[i] = (i % 100 == 0) ? 1.0 : 0.0;
        }
        for(int i = 0; i < fftLength; i++)
        {
            power[i] = 0.5 + 0.5 * sin(i);
        }

        clock_t begin;
        begin = clock();
        PlatinumResidualCalculator calc(fftLength);
        double *actual;
        QSharedPointer<double> result;
        QSharedPointer<double> powerShared(power);
        for(int i = 0; i < amount; i++)
            result = calc.calculate(fWave, waveLength / 2, f0, powerShared);
        actual = result.data();
        printf("PlatinumResidualCaclulator elapsed time = %lf[sec]\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
        begin = clock();
        for(int i = 0; i < amount; i++)
            GetOneFrameResidualSpec(dWave, waveLength, fs / f0, &forward, &ma, power, waveLength / 2, fftLength, expect);
        printf("Original Platinum elapsed time = %lf[sec]\n", (double)(clock() - begin) / CLOCKS_PER_SEC);

        QCOMPARE((float)actual[0], (float)expect[0]);
        for(int i = 1; i < fftLength - 1; i++)
        {
            QCOMPARE((float)actual[i + 1], (float)expect[i]);
        }
        QCOMPARE((float)actual[1], (float)expect[fftLength - 1]);
        delete[] expect;
        delete[] dWave;
        DestroyMinimumPhaseAnalysis(&ma);
        DestroyForwardRealFFT(&forward);
    }
};

}

DECLARE_TEST(stand::PlatinumResidualCalculatorTest)

#endif // PLATINUMRESIDUALCALCULATORTEST_H
