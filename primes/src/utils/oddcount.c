#include "utils.h"
size_t sixkCount(size_t upperBound);

size_t oddCount(bounds const *bounds)
{
    size_t half = sixkCount( bounds->upperBound) - sixkCount( bounds->lowerBound);

//    if (isOdd(bounds->lowerBound) || isOdd(bounds->upperBound))
//        half++;
//
//    if (isOdd(bounds->upperBound))  // since the interval is half-open, we
//        half--;                     // should correct for the upper bound.

    return half;
}

size_t sixkCount(size_t upperBound)
{
    if (upperBound< 5) return 0;
    size_t half = upperBound / 6 *2;
    if ((upperBound%6 == 0) || (upperBound%6 == 1))
        half--;
    return half;
}