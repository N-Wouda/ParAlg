#include "utils.h"


bounds const blockBounds(bounds const *bounds, size_t numProcs, size_t pid)
{
    size_t const range = bounds->upperBound - bounds->lowerBound;

    // With this block size and the adjustment below, the final processor has
    // at most numProcs more elements to process. When the range is large,
    // this difference is negligible.
    size_t const blockSize = range / numProcs;

    size_t const blockLowerBound = bounds->lowerBound + pid * blockSize - (((bounds->lowerBound + pid * blockSize % 6)== 1 || (bounds->lowerBound + pid * blockSize % 6)== 5));

    //printf("adapt blockLowerBound: %d", (((blockLowerBound % 6)== 1 || (blockLowerBound % 6)== 5)));
    // For the last block, we need to make sure the overall upper bound is
    // respected. If this is not the last block, the upper bound is the start
    // of the next block, as the sieve operates on a half-open interval.
    size_t const blockUpperBound = pid == numProcs - 1
                                   ? bounds->upperBound
                                   : bounds->lowerBound + (pid + 1) * blockSize - (((bounds->lowerBound + (pid + 1) * blockSize % 6)== 1 || (bounds->lowerBound + (pid + 1) * blockSize % 6)== 5));
    //if (((bounds->lowerBound % 6)== 1 || (bounds->lowerBound % 6)== 5)) blockUpperBound += 1;
    //if (((bounds->upperBound % 6)== 1 || (bounds->upperBound % 6)== 5)) blockUpperBound += 1;
    //printf("blockLowerBound: %zu, blockUpperBound%zu \n",blockLowerBound, blockUpperBound);

    return (struct bounds) {blockLowerBound, blockUpperBound};
}
