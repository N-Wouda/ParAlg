#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#include "bsp/bsp.h"

#include "primes.h"


// TODO: Mutable global state, fairly ugly. Does this work across machines?
bounds const *BSP_BOUNDS_;
long BSP_NUM_PROCS_;



bounds const blockBounds_(bounds const *bounds, size_t numProcs, size_t pid);



void bspSieve()
{
    bsp_begin(BSP_NUM_PROCS_);

    bounds const bounds = blockBounds_(
        BSP_BOUNDS_,
        BSP_NUM_PROCS_,
        bsp_pid());

    size_t numPrimes = 0;
    size_t *primes = boundedSieve(&bounds, &numPrimes);
    //printf("Primes    = %zu lower and upper %zu - %zu \n",  numPrimes ,bounds.lowerBound, bounds.upperBound);
//    for (size_t idx = 0; idx != numPrimes; ++idx)
//        printf("P %lu found: %zu\n", bsp_pid(), primes[idx]);
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
