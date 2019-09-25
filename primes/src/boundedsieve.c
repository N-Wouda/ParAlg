#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "primes.h"
#include "utils/utils.h"


size_t *smallPrimes(size_t upperBound, size_t *numSmallPrimes);

size_t *boundedSieve(bounds const *bounds, size_t *numPrimes)
{
    if (bounds->lowerBound == 0)
        return sieve(bounds, numPrimes);

    assert(bounds->upperBound > bounds->lowerBound);  // sanity check.

    bool *isPrime = init_(bounds);

    // These are all primes in the candidate region [0, sqrt(upperBound)],
    // similar to the regular sequential algorithm.
    size_t numSmallPrimes = 0;
    size_t *primes = smallPrimes(bounds->upperBound, &numSmallPrimes);

    size_t range = bounds->upperBound - bounds->lowerBound;

    for (size_t idx = 0; idx != numSmallPrimes; ++idx)
    {
        size_t prime = primes[idx];

        if (bounds->lowerBound % prime == 0)
            isPrime[0] = false;

        unmark_(isPrime, range, prime - bounds->lowerBound % prime, prime);
    }

    *numPrimes = countPrimes_(isPrime, range);
    size_t *result = getPrimes_(isPrime, bounds, *numPrimes);

    free(isPrime);      // clean-up helper arrays.
    free(primes);

    return result;
}

size_t *smallPrimes(size_t upperBound, size_t *numSmallPrimes)
{
    struct bounds candidateBounds = {0, sqrt(upperBound) + 1};
    return sieve(&candidateBounds, numSmallPrimes);
}
