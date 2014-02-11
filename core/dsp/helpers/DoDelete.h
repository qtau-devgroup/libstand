/* DoDelete.h from libstand http://github.com/qtau-devgroup/libstand by Hal@ShurabaP, BSD license */
#ifndef DODELETE_H
#define DODELETE_H

namespace stand
{
namespace helper
{

template <typename T> void DoDelete(T buf[])
{
    delete[] buf;
}

}
}

#endif // DODELETE_H
