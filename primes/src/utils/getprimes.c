#include <stdlib.h>
#include <assert.h>

#include "utils.h"


size_t *getPrimes(bool const *isPrime, bounds const *bounds, size_t numPrimes)
{
    size_t *primes = malloc(numPrimes * sizeof(size_t));

    size_t size = oddCount(bounds);    // regular size of isPrime
    size_t counter = 0;

    if (bounds->lowerBound == 0)        // Since two is the only even prime,
    {                                   // it is not regularly in isPrime and
        primes[0] = 2;                  // must be handled separately.
        counter++;
        size++;
    }

    for (size_t idx = 0; idx != size; ++idx)
        if (isPrime[idx])
            primes[counter++] = idx2num(idx, bounds->lowerBound);

    assert(counter == numPrimes);       // sanity check.

    return primes;
}
