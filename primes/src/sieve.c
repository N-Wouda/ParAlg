#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "primes.h"
#include "utils/utils.h"


size_t *sieve(bounds const *bounds, size_t *numPrimes)
{
    assert(bounds->upperBound >= 2);             // sanity checks.
    assert(bounds->lowerBound == 0);

    bool *isPrime = init_(bounds);      // marks all numbers prime.

    for (size_t number = 2; number * number < bounds->upperBound; ++number)
        if (isPrime[number])
            // If this number is prime, then it is a proper divisor for any of
            // its multiples. Note that any multiples less than the square have
            // already been unmarked at this point.
            unmark_(isPrime, bounds->upperBound, number * number, number);

    *numPrimes = countPrimes_(isPrime, bounds->upperBound);
    size_t *result = getPrimes_(isPrime, bounds, *numPrimes);

    free(isPrime);

    return result;
}
