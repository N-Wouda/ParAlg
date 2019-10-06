#include <stdlib.h>

#include <bsp.h>
#include <assert.h>
#include <stdio.h>

#include "sieve.h"
#include "utils.h"

static void stepAssignBounds();     // these neatly decouple the super-steps
static void stepComputePrimes();    // into separate functions.
static void stepComputeGoldbach();

_Thread_local bounds BSP_PROC_BOUNDS;

void bspSieve()
{
    assert(BSP_NUM_PROCS > 0);      // sanity check.

    bsp_begin(BSP_NUM_PROCS);

    stepAssignBounds();     // First we compute the bounds for each processor
    bsp_sync();             // task, and distribute those.

    stepComputePrimes();    // After receiving the bounds, each processor
    bsp_sync();             // computes primes within its sub-interval.

#ifdef GOLDBACH
    stepComputeGoldbach();
    bsp_sync();
#endif

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

    // Receive the given bounds..
    bsp_move(&BSP_PROC_BOUNDS, sizeof(struct bounds));

    size_t numPrimes = 0;   // ..and compute primes.
    size_t *primes = boundedSieve(&BSP_PROC_BOUNDS, &numPrimes);

#ifdef GOLDBACH
    for (size_t processor = 0; processor != bsp_nprocs(); ++processor)
        bsp_send(processor, NULL, primes, sizeof(size_t) * numPrimes);
#endif

    free(primes);
}

int size_tComp(void const *a, void const *b)
{
    size_t const first = *(size_t *) a;
    size_t const second = *(size_t *) b;

    // See e.g. here https://stackoverflow.com/a/10996555/4316405
    return (first < second) ? -1 : (first > second);
}

static void stepComputeGoldbach()
{
    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    if (messages != bsp_nprocs())   // we expect a message from each processor.
        bsp_abort("Processor %u expected %u sets of primes, got %u.",
                  bsp_pid(),
                  bsp_nprocs(),
                  messages);

    size_t const numPrimes = qSize / sizeof(size_t);
    size_t *primes = malloc(qSize);
    size_t offset = 0;

    for (size_t message = 0; message != bsp_nprocs(); ++message)
    {
        size_t mSize;
        bsp_get_tag(&mSize, NULL);

        bsp_move(primes + offset, mSize);
        offset += mSize / sizeof(size_t);
    }

    qsort(primes, numPrimes, sizeof(size_t), size_tComp);

    size_t const from = BSP_PROC_BOUNDS.lowerBound >= 4
        ? BSP_PROC_BOUNDS.lowerBound + isOdd(BSP_PROC_BOUNDS.lowerBound)
        : 4;

    for (size_t candidate = from;
         candidate < BSP_PROC_BOUNDS.upperBound;
         candidate += 2)
    {
        bool decomposes = false;

        for (size_t idx = 0; idx != numPrimes; ++idx)
        {
            size_t const prime = primes[idx];

            if (2 * prime > candidate)
                break;

            size_t const otherPrime = candidate - prime;

            size_t *found = (size_t *) bsearch(&otherPrime,
                                               primes,
                                               numPrimes,
                                               sizeof(size_t),
                                               size_tComp);

            if (found != NULL)
            {
                decomposes = true;
                break;
            }
        }

        if (!decomposes)
            printf(
                "Candidate %zu cannot be expressed as the sum of two primes!\n",
                candidate);
    }

    free(primes);
}
