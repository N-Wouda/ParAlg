#include "utils.h"


bounds const blockBounds(bounds const *bounds, size_t numProcs, size_t pid)
{
    size_t const range = bounds->upperBound - bounds->lowerBound;

    // With this block size and the adjustment below, the final processor has
    // at most numProcs more elements to process. When the range is large,
    // this difference is negligible.
    size_t const blockSize = range / numProcs;

    size_t lowerBound = bounds->lowerBound + pid * blockSize;

    // The edgeCase determines if the bounds
    size_t edgeCase = ((lowerBound % 6)== 1 || (lowerBound % 6)== 5);
    size_t const blockLowerBound =  lowerBound - edgeCase;

    // For the last block, we need to make sure the overall upper bound is
    // respected. If this is not the last block, the upper bound is the start
    // of the next block, as the sieve operates on a half-open interval.

    size_t upperBound = bounds->lowerBound + (pid + 1) * blockSize;
    edgeCase = ((upperBound % 6) == 1 || (upperBound % 6) == 5);
    size_t const blockUpperBound = pid == numProcs - 1
                                   ? bounds->upperBound
                                   : upperBound - edgeCase;

    return (struct bounds) {blockLowerBound, blockUpperBound};
}
