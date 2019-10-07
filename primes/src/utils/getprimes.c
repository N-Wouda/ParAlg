#include <stdlib.h>
#include <assert.h>

#include "utils.h"


size_t *getPrimes(bool const *isPrime, bounds const *bounds, size_t numPrimes)
{

    size_t size = oddCount(bounds) + (bounds->lowerBound>2); // size of isPrime

    size_t counter = 0;

    if (numPrimes == 0)                 // there are no numbers in this
        return NULL;                    // interval, let alone primes.

    size_t *primes = malloc(numPrimes * sizeof(size_t));

    if (bounds->lowerBound <= 2)        // Since two and three are not 6k+-1,
    {                                   // it is not in isPrime and
        primes[0] = 2;                  // must be handled separately.
        primes[1] = 3;
        size += 2;
        counter = 2;
    }

    for (size_t idx = 0; idx != size; ++idx)
    {
        if (isPrime[idx])
        {
            primes[counter++] = idx2num(idx, bounds->lowerBound);
        }
    }

    //assert(counter == numPrimes);       // sanity check.

    return primes;
}
