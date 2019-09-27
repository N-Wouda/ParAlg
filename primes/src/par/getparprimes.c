#include <stdlib.h>
#include <assert.h>

#include "par.h"


size_t *getParPrimes_(bool const *isPrime,
                      bounds const *bounds,
                      size_t numPrimes)
{
    size_t const range = bounds->upperBound - bounds->lowerBound;

    size_t *primes = malloc(numPrimes * sizeof(size_t));
    size_t counter = 0;

    for (size_t number = 0; number != range; ++number)
        if (isPrime[number])
            primes[counter++] = bounds->lowerBound + number;

    assert(counter == numPrimes);   // sanity check.

    return primes;
}