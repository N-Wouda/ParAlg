#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "sieve.h"
#include "utils.h"


size_t *boundedSieve(bounds *bounds, size_t *numPrimes)
{
    // This shifts the bounds if they fall exactly on numbers of the form
    // 6k +- 1. Note that shifting the interval one place to the left does
    // not change the primes we find.
    bounds->lowerBound -= ((bounds->lowerBound % 6) == 1
        || (bounds->lowerBound % 6) == 5);

    bounds->upperBound -= ((bounds->upperBound % 6) == 1
        || (bounds->upperBound % 6) == 5);

    if (bounds->lowerBound <= 2)        // this is the `regular' case.
    {
        struct bounds const zeroBound = {0, bounds->upperBound};
        return sieve(&zeroBound, numPrimes);
    }

    assert(bounds->upperBound >= 2);    // sanity checks.
    assert(bounds->upperBound > bounds->lowerBound);

    // This represents all candidates in the given interval. We skip over
    // index zero, so we reserve a little extra space.
    size_t const size = 1 + candidateCount(bounds);

    bool *isPrime = init(bounds);       // marks all numbers in bounds prime.

    // These are all primes in the candidate region [0, sqrt(upperBound)),
    // similar to the regular sequential algorithm.
    size_t numCandPrimes = 0;
    struct bounds candidateBounds = {0, sqrt(bounds->upperBound) + 1 };

    // This modification has the same motivation as the one above for the
    // overall bounds.
    candidateBounds.upperBound += (candidateBounds.upperBound % 6 == 1)
        || (candidateBounds.upperBound % 6 == 5);

    size_t *candPrimes = sieve(&candidateBounds, &numCandPrimes);

    // Equipped with these primes, we unmark all their multiples within the
    // interval. Observe that we must skip two and three. We unmark all
    // multiples of the form 6k - 1 and 6k + 1 separately in two passes,
    // as their stride is constant for each.
    for (size_t idx = 2; idx != numCandPrimes; ++idx)
    {
        size_t const prime = candPrimes[idx];

        // Unmark all multiples of the given prime in the isPrime array. We can
        // start marking off from the first multiple of the prime in isPrime.
        size_t from = bounds->lowerBound + prime - bounds->lowerBound % prime;
        size_t const modFrom = from % 6;

        // If the current multiple is not yet of the form 6k +- 1, we need to
        // iterate ahead until it is.
        if (modFrom != 5 && modFrom != 1)
        {
            if (prime % 6 == 5)
                // If this prime is just short of a multiple of six, we count
                // down towards the first multiple of the form 6k + 1. This
                // takes modFrom - 1 steps. When we are currently at a multiple
                // of six, we need to jump the full five steps instead.
                from += modFrom != 0 ? (modFrom - 1) * prime : 5 * prime;
            else
                // Else we have a prime just larger than a multiple of six and
                // we count up, towards 6k - 1. This takes 5 - modFrom steps.
                from += (5 - modFrom) * prime;
        }

        // Unmark the first form, either 6k + 1, or 6k - 1.
        unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2 * prime);

        // After unmarking the first form, the other remains. The other case is
        // either at distance two if we jump over a multiple of six, as
        // 5 -> 0 -> 1, or 1 -> 0 -> 5, or four, when we do not, as
        // 1 -> 2 -> .. -> 5, or 5 -> 4 -> .. -> 1.
        if ((prime % 6 == 5 && from % 6 == 5)
                || (prime % 6 == 1 && from % 6 == 1))
            from += 2 * prime;

        from += 2 * prime;

        unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2 * prime);
    }

    *numPrimes = countPrimes(isPrime, size);
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);
    free(candPrimes);

    return result;
}
