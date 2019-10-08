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
    // 6k +- 1. Note that in these case shifting the interval one place to the
    // left does not change the primes we find.
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
    // interval. Observe that we must skip two and three, the first primes at
    // index 0 and 1 as we do not store these in isPrime. We unmark all
    // multiples which are of the form 6k - 1 and 6k+1 separately as each has a
    // fixed number of values in isPrime in between: 6 * prime.
    for (size_t idx = 2; idx != numCandPrimes; ++idx)
    {
        size_t const prime = candPrimes[idx];

        // Unmark all multiples of the given prime in the isPrime array. We can
        // start marking off from the first multiple of the prime in isPrime.
        size_t from = bounds->lowerBound + prime - bounds->lowerBound % prime;

        // Starting at from, we need to find the first multiple that is of the
        // form 6k +- 1. These we unmark.
        while ((from % 6 != 1) && (from % 6 != 5))
            from += prime;

        unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2 * prime);

        // Thereafter, we still have other multiples: if we unmarked all of the
        // form 6k + 1, we should now do 6k - 1, and vice versa.
        from += prime;

        while ((from % 6 != 1) && (from % 6 != 5))
            from += prime;

        unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2 * prime);
    }

    *numPrimes = countPrimes(isPrime, size);
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);
    free(candPrimes);

    return result;
}
