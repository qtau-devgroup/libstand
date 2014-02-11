/* Decimator.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef DECIMATOR_H
#define DECIMATOR_H

namespace stand
{

class Signal;

class Decimator
{
public:
    static void filter(double *inout, int length, int ratio);
    static void decimate(const Signal &src, int ratio, double *dst, int dstLength);
};

}

#endif // DECIMATOR_H
