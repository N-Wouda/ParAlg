#include "utils.h"


static size_t countUpTo(size_t upperBound);     // helper method

size_t candidateCount(bounds const *bounds)
{
    return countUpTo(bounds->upperBound) - countUpTo(bounds->lowerBound);
}

static size_t countUpTo(size_t upperBound)
{
    if (upperBound < 5)     // pathological case where there is no candidate
        return 0;           // to consider.

    // Generally, we have two candidates around every multiple of six.
    size_t count = upperBound / 6 * 2;

    // Except when the upper bound excludes 6k + 1, in which case we should
    // remove it from the count.
    if ((upperBound % 6 == 0) || (upperBound % 6 == 1))
        count--;

    return count;
}
