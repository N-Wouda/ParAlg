#include <stdlib.h>

#include <bsp.h>

#include "primes.h"


extern long BSP_NUM_PROCS;
extern bounds const *BSP_BOUNDS;

static void stepAssignBounds();     // these neatly decouple the super-steps
static void stepComputePrimes();    // into separate functions.

bounds const blockBounds_(bounds const *bounds, size_t numProcs, size_t pid);

void bspSieve()
{
    bsp_begin(BSP_NUM_PROCS);

    stepAssignBounds();     // First we compute the bounds for each processor
    bsp_sync();             // task, and distribute those.

    stepComputePrimes();    // After receiving the bounds, each processor
    bsp_sync();             // computes primes within this sub-interval.

    bsp_end();
}

static void stepAssignBounds()
{
    if (bsp_pid() == 0)     // The first processor determines the bounds for
    {                       // all others.
        for (size_t processor = 0; processor != bsp_nprocs(); ++processor)
        {
            bounds const bounds = blockBounds_(
                BSP_BOUNDS,
                BSP_NUM_PROCS,
                processor);

            // Send *one* message to each processor, containing the lower
            // and upper bound.
            bsp_send(processor, NULL, &bounds, sizeof(struct bounds));
        }
    }
}

static void stepComputePrimes()
{
    unsigned int messages;
    bsp_qsize(&messages, NULL);

    if (messages != 1)      // we expect *one* message containing the bounds.
        bsp_abort("Processor %u did not receive bounds.", bsp_pid());

    bounds bounds;          // Receive the given bounds..
    bsp_move(&bounds, sizeof(struct bounds));

    size_t numPrimes = 0;   // ..and compute primes.
    size_t *primes = boundedSieve(&bounds, &numPrimes);

    free(primes);
}

bounds const blockBounds_(bounds const *bounds, size_t numProcs, size_t pid)
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
