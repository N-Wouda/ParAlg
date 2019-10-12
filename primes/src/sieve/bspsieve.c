#include <stdlib.h>

#include <bsp.h>
#include <assert.h>

#include "sieve.h"
#include "utils.h"


static void stepAssignBounds();     // these neatly decouple the super-steps
static void stepComputePrimes();    // into separate functions.

void bspSieve()
{
    assert(BSP_NUM_PROCS > 0);        // sanity check.

    bsp_begin(BSP_NUM_PROCS);

    stepAssignBounds();     // First we compute the bounds for each processor
    bsp_sync();             // task, and distribute those.

    stepComputePrimes();    // After receiving the bounds, each processor
    bsp_sync();             // computes primes within its sub-interval.

    bsp_end();
}

static void stepAssignBounds()
{
    if (bsp_pid() == 0)     // The first processor determines the bounds for
    {                       // all others.
        for (size_t processor = 0; processor != bsp_nprocs(); ++processor)
        {
            bounds const bounds = blockBounds(
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

    // TODO: Here you would, presumably, want to use these prime numbers.

    free(primes);
}
