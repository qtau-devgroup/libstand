/* DioF0Estimator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef DIOF0ESTIMATOR_H
#define DIOF0ESTIMATOR_H

#include <QPair>
#include "dsp/F0Estimator.h"

namespace stand
{

class Fft;
class Signal;

/**
 * @brief The DioF0Estimator class is an implementation of F0Estimator.
 *        DIO is a fast algorithm to estimate F0 contour.
 * @see   http://www.slp.is.ritsumei.ac.jp/~morise/world/
 * @author Hal@shurabaP
 */
class DioF0Estimator : public F0Estimator
{
public: // public constants
    static const double DefaultF0Floor;
    static const double DefaultF0Ceil;
    static const double DefaultChannelsInOctave;
    static const double DefaultDecimatedFs;
public:
    /**
     * @brief DioF0Estimator is a constructor.
     * @param f0Floor is a low-limit for estimation.
     * @param f0Ceil is a high-limit for estimation.
     * @param channelsInOctave
     * @param decimatedFs
     */
    explicit DioF0Estimator(
            double f0Floor = DefaultF0Floor,
            double f0Ceil = DefaultF0Ceil,
            double channelsInOctave = DefaultChannelsInOctave,
            double decimatedFs = DefaultDecimatedFs);

    /**
     * @brief estimate estimates F0 countour.
     * @param wave is a signal to estimate F0.
     * @param msFramePeriod is a period length of estimation.
     * @return F0 contour.
     */
    Contour<float> estimate(const Signal &wave, double msFramePeriod);
private:
    double floorF0;
    double ceilF0;
    double channelsInOctave;
    double decimatedFs;
    int bandsCount;
    Fft *fft;

    typedef struct Spectrum
    {
        Spectrum(const Spectrum &other)
        {
            data = other.data;
            length = other.length;
            size = other.size;
            fs = other.fs;
        }
        Spectrum(double *spectrum, int length, int size, double fs)
        {
            this->data = spectrum;
            this->length = length;
            this->size = size;
            this->fs = fs;
        }
        ~Spectrum()
        {
            delete[] data;
        }

        double *data;
        int length; // length of wave
        int size;   // size of FFT
        double fs;
    } Spectrum;

    Spectrum createDecimatedSpectrum(const Signal &signal, int decimationRatio);
    void getFilteredSignal(double *dst, int halfAverageLength, const Spectrum &spectrum);
    Contour<float> estimate(const Spectrum &spectrum, int length, int fs, double msFramePeriod);
};

}

#endif // DIOF0ESTIMATOR_H
