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

    bool *isPrime = init(bounds);               // marks all numbers prime.

    for (size_t number = 2; number * number < bounds->upperBound; ++number)
        if (isPrime[number])
            // If this number is prime, then it is a proper divisor for any of
            // its multiples. Note that any multiples less than the square have
            // already been unmarked at this point.
            unmark(isPrime, bounds->upperBound, number * number, number);

    *numPrimes = countPrimes(isPrime, bounds->upperBound);
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);

    return result;
}
