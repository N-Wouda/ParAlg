#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "primes.h"
#include "utils.h"


size_t *boundedSieve(bounds const *bounds, size_t *numPrimes)
{
    if (bounds->lowerBound <= 2)            // this is the `regular' case.
    {
        struct bounds zeroBound = {0, bounds->upperBound};
        return sieve(&zeroBound, numPrimes);
    }

    assert(bounds->upperBound >= 2);        // sanity checks.
    assert(bounds->upperBound > bounds->lowerBound);

    size_t const size = oddCount_(bounds);

    bool *isPrime = init_(bounds);      // marks all numbers in bounds prime.

    // These are all primes in the candidate region [0, sqrt(upperBound)),
    // similar to the regular sequential algorithm.
    size_t numCandPrimes = 0;
    struct bounds candidateBounds = {0, sqrt(bounds->upperBound) + 1};

    size_t *candPrimes = sieve(&candidateBounds, &numCandPrimes);

    // Equipped with these primes, we unmark all their multiples within the
    // interval. Observe that we must skip two, the first prime.
    for (size_t idx = 1; idx != numCandPrimes; ++idx)
    {
        size_t prime = candPrimes[idx];

        if (bounds->lowerBound != prime && bounds->lowerBound % prime == 0)
            isPrime[0] = false;

        // Unmark all multiples of the given prime in the isPrime array. We can
        // start marking off from the first multiple of the prime in isPrime,
        // or its square, whichever is highest.
        size_t from = prime * prime > bounds->lowerBound
            ? prime * prime
            : bounds->lowerBound + prime - bounds->lowerBound % prime;

        if (from % 2 == 0)  // from is even so the next multiple is odd, and we
            from += prime;  // start there, as we do not store even numbers.

        unmark_(isPrime, size, num2idx_(from, bounds->lowerBound), prime);
    }

    *numPrimes = countPrimes_(isPrime, size);
    size_t *result = getPrimes_(isPrime, bounds, *numPrimes);

    free(isPrime);
    free(candPrimes);

    return result;
}
