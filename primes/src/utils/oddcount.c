#include "utils.h"


size_t oddCount_(bounds const *bounds)
{
    size_t half = (bounds->upperBound - bounds->lowerBound) / 2;

    // If either the lower or upper bound is odd, we add one to the count. Note
    // that the upper bound is corrected below.
    if (bounds->lowerBound % 2 || bounds->upperBound % 2)
        half++;

    if (bounds->upperBound % 2)     // since the interval is half-open, we
        half--;                     // should correct for the upper bound.

    return half;
}
