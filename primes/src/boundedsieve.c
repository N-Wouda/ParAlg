#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "primes.h"
#include "utils/utils.h"


size_t *boundedSieve(bounds const *bounds, size_t *numPrimes)
{
    if (bounds->lowerBound == 0)            // this is the `regular' case.
        return sieve(bounds, numPrimes);

    assert(bounds->upperBound >= 2);        // sanity checks.
    assert(bounds->upperBound > bounds->lowerBound);

    bool *isPrime = init(bounds);           // marks all numbers prime.

    // These are all primes in the candidate region [0, sqrt(upperBound) + 1),
    // similar to the regular sequential algorithm.
    size_t numCandPrimes = 0;
    struct bounds const candidateBounds = {0, sqrt(bounds->upperBound) + 1};

    size_t *candPrimes = sieve(&candidateBounds, &numCandPrimes);
    size_t const range = bounds->upperBound - bounds->lowerBound;

    // Equipped with these primes, we unmark all their multiples within the
    // interval.
    for (size_t idx = 0; idx != numCandPrimes; ++idx)
    {
        size_t prime = candPrimes[idx];

        // Since we unmark from the first multiple *after* the lower bound, we
        // need to check the lower bound itself explicitly.
        if (bounds->lowerBound % prime == 0)
            isPrime[0] = false;

        // Unmark all multiples of the given prime in the isPrime array. Note
        // the unusual set-up as we translate from block range to index range.
        unmark(isPrime, range, prime - bounds->lowerBound % prime, prime);
    }

    *numPrimes = countPrimes(isPrime, range);
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);
    free(candPrimes);

    return result;
}
