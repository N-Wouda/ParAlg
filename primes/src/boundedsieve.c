#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "primes.h"
#include "utils/utils.h"


size_t *boundedSieve(bounds const *bounds, size_t *numPrimes)
{
    assert(bounds->upperBound > bounds->lowerBound);  // sanity check.

    size_t range = bounds->upperBound - bounds->lowerBound;

    bool *isPrime = init_(range);

    for (size_t number = 2; number * number < bounds->upperBound; ++number)
    {
        size_t remainder = bounds->lowerBound % number;

        size_t firstMultiple = remainder
            ? bounds->lowerBound + number - remainder
            : bounds->lowerBound;

        if (isPrime[firstMultiple - bounds->lowerBound])
            unmark_(isPrime, range, firstMultiple - bounds->lowerBound, number);
    }

    *numPrimes = countPrimes_(isPrime, range);
    size_t *result = getPrimes_(isPrime, bounds, *numPrimes);

    free(isPrime);      // clean-up helper array.

    return result;
}
