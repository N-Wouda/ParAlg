#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bsp/bsp.h"

#include "primes.h"

size_t _NUM_PROCS;          // TODO: Mutable global state. This is so ugly I
bounds const *_BOUNDS;      // TODO: want to claw my eyes out.

void bspSieve_();

bounds blockBounds_(bounds const *bounds, size_t numProcs, size_t pid);

void bspSieve(bounds const *bounds, size_t numProcs)
{
    assert(numProcs > 0);

    // TODO: Temp. requirement until we have fixed the block allocation below.
    assert((bounds->upperBound - bounds->lowerBound) % numProcs == 0);

    bsp_init(bspSieve_, 0, 0);  // not sure if this is needed.

    _NUM_PROCS = numProcs;
    _BOUNDS = bounds;

    bspSieve_();
}

void bspSieve_()
{
    bsp_begin(_NUM_PROCS);

    bounds bounds = blockBounds_(_BOUNDS, _NUM_PROCS, bsp_pid());

    size_t numPrimes = 0;
    size_t * primes = boundedSieve(&bounds, &numPrimes);

    printf("Primes in process %u: %zu.\n", bsp_pid(), numPrimes);

    for (size_t idx = 0; idx != numPrimes; ++idx)
        printf("Process %u: prime %zu.\n", bsp_pid(), primes[idx]);

    free(primes);

    bsp_end();
}

bounds blockBounds_(bounds const *bounds, size_t numProcs, size_t pid)
{
    size_t offset = bounds->lowerBound;
    size_t range = bounds->upperBound - bounds->lowerBound;

    // TODO: Get this to play nice with the edge cases.
    size_t blockSize = range / numProcs;

    return (struct bounds) {
        offset + pid * blockSize,
        offset + (pid + 1) * blockSize
    };
}
