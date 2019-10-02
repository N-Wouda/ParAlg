#include "utils.h"


size_t oddCount(bounds const *bounds)
{
    size_t half = (bounds->upperBound - bounds->lowerBound) / 2;

    if (isOdd(bounds->lowerBound) || isOdd(bounds->upperBound))
        half++;

    if (isOdd(bounds->upperBound))  // since the interval is half-open, we
        half--;                     // should correct for the upper bound.

    return half;
}
