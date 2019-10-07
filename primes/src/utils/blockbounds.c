#include "utils.h"


bounds const blockBounds(bounds const *bounds, size_t numProcs, size_t pid)
{
    size_t const range = bounds->upperBound - bounds->lowerBound;
    size_t const blockSize = range / numProcs;

    size_t const blockLowerBound = bounds->lowerBound + pid * blockSize;

    // For the last block, we need to make sure the overall upper bound is
    // respected. If this is not the last block, the upper bound is the start
    // of the next block, as the sieve operates on a half-open interval.
    size_t const blockUpperBound = pid == numProcs - 1
                                   ? bounds->upperBound
                                   : bounds->lowerBound + (pid + 1) * blockSize;

    return (struct bounds) {blockLowerBound, blockUpperBound};
}
