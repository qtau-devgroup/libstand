/* MinimumPhaseTest.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef MINIMUM_PHASE_TEST_H
#define MINIMUM_PHASE_TEST_H

#include <float.h>
#include "dsp/MinimumPhase.h"
#include "AutoTest.h"
#include "dsp/world/common.h"

namespace stand
{

// Compare accuracy
const double Epsilon = 0.01;

class MinimumPhaseTest : public QObject
{
    Q_OBJECT
private slots:
    void minimum_phase_spectrum_of_gaussian_noise_is_white_spectrum()
    {
        int fftLength = 32;
         MinimumPhase mp(fftLength);
         double *power = new double[fftLength];
         for(int i = 0; i < fftLength; i++)
         {
             power[i] = 1.0;
         }
         QSharedPointer<double> result(mp.execute(QSharedPointer<double>(power)));
         double *out = result.data();
         for(int i = 1; i < fftLength / 2; i++)
         {
             QCOMPARE(out[i * 2], 1.0);
             QCOMPARE(out[i * 2 + 1] + 1.0, 1.0); // Needs plus 1.0 to compare zero with QCOMPARE.
         }
         QCOMPARE(out[0], 1.0);
         QCOMPARE(out[1], 1.0);
     }

    void minimum_phase_spectrum_of_single_pulse_is_single_pulse()
    {
        int fftLength = 32;
        MinimumPhase mp(fftLength);
        double *power = new double[fftLength];
        power[0] = 1.0;
        for(int i = 1; i < fftLength; i++)
        {
            power[i] = 0.0;
        }
        QSharedPointer<double> result(mp.execute(QSharedPointer<double>(power)));
        double *out = result.data();
        QCOMPARE(out[0], 1.0);
        QCOMPARE(out[1] + 1.0, 1.0);
        for(int i = 1; i < fftLength; i++)
        {
            QCOMPARE(out[i] + 1.0, 1.0); // Needs plus 1.0 to compare zero with QCOMPARE.
        }
    }

    void the_result_of_MinimumPhase_execute_must_equal_to_worlds_minimum_phase_analysis()
    {
        int fftLength = 32;
        MinimumPhase mp(fftLength);
        MinimumPhaseAnalysis ma;
        InitializeMinimumPhaseAnalysis(fftLength, &ma);
        double *power = new double[fftLength];
        for(int i = 0; i < fftLength; i++)
        {
            power[i] = (double)rand() / RAND_MAX;
            ma.log_spectrum[i] = log(power[i] + DBL_MIN) / 2;
        }
        QSharedPointer<double> result(mp.execute(QSharedPointer<double>(power)));
        double *out = result.data();
        GetMinimumPhaseSpectrum(&ma);
        for(int i = 1; i < fftLength / 2; i++)
        {
            QCOMPARE(out[i * 2], ma.minimum_phase_spectrum[i][0]);
            QCOMPARE(out[i * 2 + 1], ma.minimum_phase_spectrum[i][1]);
        }
        QCOMPARE(out[0], ma.minimum_phase_spectrum[0][0]);
        QCOMPARE(out[1], ma.minimum_phase_spectrum[fftLength / 2][0]);
    }
};

}

DECLARE_TEST(stand::MinimumPhaseTest)

#endif // MINIMUM_PHASE_TEST_H
