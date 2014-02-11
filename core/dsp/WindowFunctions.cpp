/* WindowFunctions.cpp from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#include <qmath.h>
#include "WindowFunctions.h"

using namespace stand;

void WindowFunctions::nuttall(double *dst, int length)
{
    for (int i = 0; i < length; ++i)
    {
        double tmp  = (i + 1 - (length + 1) / 2.0) / (length + 1);
        dst[i] = 0.355768 + 0.487396 * cos(2 * M_PI * tmp) + 0.144232 * cos(4.0 * M_PI * tmp) + 0.012604 * cos(6.0 * M_PI * tmp);
    }
}
