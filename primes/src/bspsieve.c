#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#include "bsp/bsp.h"

#include "primes.h"


// TODO: Mutable global state, fairly ugly. Does this work across machines?
bounds const *BSP_BOUNDS_;
size_t BSP_NUM_PROCS_;

void bspSieve_();

bounds const blockBounds_(bounds const *bounds, size_t numProcs, size_t pid);

void bspSieve(bounds const *bounds, size_t numProcs)
{
    assert(numProcs > 0);   // sanity check.

    BSP_BOUNDS_ = bounds;
    BSP_NUM_PROCS_ = numProcs;

    bsp_init(bspSieve_, 0, 0);  // not sure if this is needed.
    bspSieve_();
}

void bspSieve_()
{
    bsp_begin(BSP_NUM_PROCS_);

    bounds const bounds = blockBounds_(
        BSP_BOUNDS_,
        BSP_NUM_PROCS_,
        bsp_pid());

    size_t numPrimes = 0;
    size_t *primes = boundedSieve(&bounds, &numPrimes);

    free(primes);

    bsp_sync();
    bsp_end();
}

bounds const blockBounds_(bounds const *bounds, size_t numProcs, size_t pid)
{
    size_t const range = bounds->upperBound - bounds->lowerBound;
    size_t const blockSize = range / numProcs + 1;

    size_t const blockLowerBound = bounds->lowerBound + pid * blockSize;

    // For the last block, we need to make sure the overall upper bound is
    // respected. If this is not the last block, the upper bound is the start
    // of the next block, as the sieve operates on a half-open interval.
    size_t const blockUpperBound = pid == numProcs - 1
        ? bounds->upperBound
        : bounds->lowerBound + (pid + 1) * blockSize;

    return (struct bounds) {blockLowerBound, blockUpperBound};
}
