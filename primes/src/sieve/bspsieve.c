#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <bsp.h>

#include "defines.h"
#include "sieve.h"
#include "utils.h"

static void stepAssignBounds();     // these neatly decouple the super-steps
static void stepComputePrimes();    // into separate functions.
static void stepComputeGoldbach();

_Thread_local bounds BSP_PROC_BOUNDS;
_Thread_local size_t ops = 0;

void bspSieve()
{
    assert(BSP_NUM_PROCS > 0);      // sanity check.

    bsp_begin(BSP_NUM_PROCS);

    stepAssignBounds();     // First we compute the bounds for each processor
    bsp_sync();             // task, and distribute those.

    stepComputePrimes();    // After receiving the bounds, each processor
    bsp_sync();             // computes primes within its sub-interval.

#ifdef GOLDBACH
    stepComputeGoldbach();  // If defined, each processor verifies Goldbach's
    bsp_sync();             // conjecture within its sub-interval.
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
    // Sends this processor's primes to all subsequent processors (and
    // ourselves), as they will need them to determine Goldbach's conjecture.
    for (size_t processor = bsp_pid(); processor != bsp_nprocs(); ++processor)
        bsp_send(processor, NULL, primes, sizeof(size_t) * numPrimes);
#endif

    free(primes);
}

static void stepComputeGoldbach()
{
    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    // We expect a message from each prior processor (and ourselves).
    if (messages != bsp_pid() + 1)
        bsp_abort("Processor %u expected %u sets of primes, got %u.",
                  bsp_pid(),
                  bsp_pid(),
                  messages);

    size_t *primes = malloc(qSize);
    size_t offset = 0;

    // Receive all primes into the primes array.
    for (size_t message = 0; message != messages; ++message)
    {
        size_t mSize;
        bsp_get_tag(&mSize, NULL);

        // After receiving mSize bytes, we must update the offset to just
        // beyond these, such that the next message may be received properly.
        bsp_move(primes + offset, mSize);
        offset += mSize / sizeof(size_t);
    }

    size_t const numPrimes = qSize / sizeof(size_t);

    // Sorts the received primes, using a comparison helper method.
    qsort(primes, numPrimes, sizeof(size_t), size_t_cmp);

    // We only need to iterate over even candidate numbers, starting from four
    // (or the first even number after the lower bound, whichever is largest).
    size_t const from = BSP_PROC_BOUNDS.lowerBound >= 4
        ? BSP_PROC_BOUNDS.lowerBound + isOdd(BSP_PROC_BOUNDS.lowerBound)
        : 4;

    for (size_t cand = from; cand < BSP_PROC_BOUNDS.upperBound; cand += 2)
    {
        bool isPrimeSum = false;

        // For the candidate number, we iterate over the primes array and
        // search for a complementary prime. If at any point we find the
        // complement, their sum equals the candidate and we may terminate.
        for (size_t idx = 0; idx != numPrimes; ++idx)
        {
            size_t const first = primes[idx];
            size_t const second = cand - first;

            if (first > second)         // at this point, we have already seen
                break;                  // the complement as first.

            void *found = bsearch(&second,  // efficiently searches for second
                                  primes,   // in the primes array.
                                  numPrimes,
                                  sizeof(size_t),
                                  size_t_cmp);

            if (found != NULL)  // if the complement exists as a prime, we have
            {                   // found two primes that sum to the candidate.
                isPrimeSum = true;
                break;
            }
        }

        if (!isPrimeSum)        // If this happens, I claim first authorship!
            printf("%zu cannot be expressed as the sum of two primes!\n",
                   cand);
    }

    printf("Ops: %zu\n", ops);

    free(primes);
}
