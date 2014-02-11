/* WorldFrame.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef WORLDFRAME_H
#define WORLDFRAME_H

#include <QSharedPointer>

namespace stand
{

/**
 * @brief The WorldFrame class represents a single frame for WORLD system.
 *        This class contains f0, spectrum, residual and FFT size.
 * @author Hal@shurabaP
 */
class WorldFrame
{
public:
    explicit WorldFrame(int fftLength, int samplingFrequency, double f0);
    WorldFrame(const WorldFrame &other);
    WorldFrame &operator =(const WorldFrame &other);

    virtual ~WorldFrame();

    /**
     * @brief clear clears spectrum and residual.
     *        `clear` means fill 1.0 into spectrum, and 0,0 into residual.
     */
    void clear();

    QSharedPointer<double> spectrum;
    QSharedPointer<double> residual;

    int fftLength;
    int samplingFrequency;
    double f0;

private:
    void destroy();
};

}

#endif // WORLDFRAME_H
