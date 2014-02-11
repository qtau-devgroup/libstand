/* FftSg.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef FFT_H
#define FFT_H

namespace stand
{

/**
 * @brief The Fft class does FFT. This class contains information for FFT.
 *        This implementation of FFT is a thin wrapper of FFT SG.
 *        See more about FFT SG below.
 * @see   http://www.kurims.kyoto-u.ac.jp/~ooura/index.html
 * @author Hal@shurabaP
 */
class Fft
{
public:
    static const int Inverse = -1;
    static const int Forward = 1;
    enum Type
    {
        Real = 1,
        Complex = 2
    };

    static int suitableLength(int sampleCount);
public:
    /**
     * @brief Fft is a basic constructor for FFT class.
     * @param fftLength is a FFT size.
     * @param type specifies which to use `complex to complex` or `real to complex` FFT.
     */
    explicit Fft(int fftLength, Type type);
    virtual ~Fft();

    /**
     * @brief execute executes FFT.
     * @param sign means a direction, -1 for invers FFT, 1 for forward FFT.
     * @param inout is a buffer. `execute` overwrites an input buffer by output data.
     */
    void execute(int sign, double *inout);

    int fftLength;
    Type type;

private:
    void createBuffer();
    void destroy();
    int *ip;
    double *w;
};

}

#endif // FFT_H
