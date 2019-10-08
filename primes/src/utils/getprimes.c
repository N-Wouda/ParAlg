#include <stdlib.h>
#include <assert.h>

#include "utils.h"


size_t *getPrimes(bool const *isPrime, bounds const *bounds, size_t numPrimes)
{
    // TODO make this work nicely when lowerBound == 2, lowerBound == 3,
    // or lowerBound < 2.
    if (numPrimes == 0)                 // There are no primes in this
        return NULL;                    // interval.

    size_t counter = 0;
    size_t size = candidateCount(bounds)    // Regular size of isPrime, with
        + (bounds->lowerBound > 2)          // allowances for when the lower
        - (bounds->lowerBound <= 3);        // bound includes two and/or three.

    size_t *primes = malloc(numPrimes * sizeof(size_t));

    if (bounds->lowerBound <= 2)        // Since two and three are not of the
    {                                   // form 6k +- 1, they are not in the
        primes[0] = 2;                  // array and are handled separately.
        primes[1] = 3;

        size += 2;
        counter = 2;
    }

    for (size_t idx = 0; idx != size; ++idx)
        if (isPrime[idx])
            primes[counter++] = idx2num(idx, bounds->lowerBound);

    assert(counter == numPrimes);       // sanity check.

    return primes;
}
