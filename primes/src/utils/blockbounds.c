#include "utils.h"


bounds const blockBounds(bounds const *bounds, size_t numProcs, size_t pid)
{
    size_t const range = bounds->upperBound - bounds->lowerBound;

    // With this block size and the adjustment below, the final processor has
    // at most numProcs more elements to process. When the range is large,
    // this difference is negligible.
    size_t const blockSize = range / numProcs;

    // For both interval bounds, we should ensure we do not split at exactly
    // a bound of the form 6k +- 1. This is done by subtracting one from the
    // bound, if needed.
    size_t const lowerBound = bounds->lowerBound + pid * blockSize;
    size_t const blockLowerBound =  lowerBound
        - ((lowerBound % 6) == 1 || (lowerBound % 6) == 5);

    // For the last block, we need to make sure the overall upper bound is
    // respected. If this is not the last block, the upper bound is the start
    // of the next block, as the sieve operates on a half-open interval.
    size_t const upperBound = bounds->lowerBound + (pid + 1) * blockSize;
    size_t const blockUpperBound = pid == numProcs - 1
        ? bounds->upperBound
        : upperBound - ((upperBound % 6) == 1 || (upperBound % 6) == 5);

    return (struct bounds) {blockLowerBound, blockUpperBound};
}
