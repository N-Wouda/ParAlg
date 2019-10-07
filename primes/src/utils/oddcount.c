#include "utils.h"
size_t sixkCount(size_t upperBound);

size_t oddCount(bounds const *bounds)
{
    size_t half = sixkCount(bounds->upperBound) - sixkCount(bounds->lowerBound);

    return half;
}

size_t sixkCount(size_t upperBound)
{
    if (upperBound< 5) return 0;
    size_t half = upperBound / 6 *2;
    if ((upperBound%6 == 0)|| (upperBound%6 == 1))
        half--;
    return half;
}