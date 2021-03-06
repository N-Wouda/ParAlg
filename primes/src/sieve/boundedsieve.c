#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "sieve.h"
#include "utils.h"


size_t *boundedSieve(bounds const *bounds, size_t *numPrimes)
{
    if (bounds->lowerBound <= 2)            // this is the `regular' case.
    {
        struct bounds const zeroBound = {0, bounds->upperBound};
        return sieve(&zeroBound, numPrimes);
    }

    assert(bounds->upperBound >= 2);        // sanity checks.
    assert(bounds->upperBound > bounds->lowerBound);

    size_t const size = oddCount(bounds);

    bool *isPrime = init(bounds);      // marks all numbers in bounds prime.

    // These are all primes in the candidate region [0, sqrt(upperBound)),
    // similar to the regular sequential algorithm.
    size_t numCandPrimes = 0;
    struct bounds candidateBounds = {0, sqrt(bounds->upperBound) + 1};

    size_t *candPrimes = sieve(&candidateBounds, &numCandPrimes);

    // Equipped with these primes, we unmark all their multiples within the
    // interval. Observe that we must skip two, the first prime at index 0,
    // as we do not store even numbers.
    for (size_t idx = 1; idx != numCandPrimes; ++idx)
    {
        size_t const prime = candPrimes[idx];

        // Since below we never start directly *at* the lower bound, this
        // explicit check is needed also. TODO merge this with from? How?
        if (bounds->lowerBound % prime == 0)
            isPrime[0] = false;

        // Unmark all multiples of the given prime in the isPrime array. We can
        // start marking off from the first multiple of the prime in isPrime,
        // or its square, if it exceeds the lower bound.
        size_t from = prime * prime > bounds->lowerBound
            ? prime * prime
            : bounds->lowerBound + prime - bounds->lowerBound % prime;

        if (isEven(from))           // from is even so the next multiple
            from += prime;          // is odd, and we may start there.

        unmark(isPrime, size, num2idx(from, bounds->lowerBound), prime);
    }

    *numPrimes = countPrimes(isPrime, size);
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);
    free(candPrimes);

    return result;
}
