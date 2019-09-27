#include <stdlib.h>
#include <assert.h>

#include "seq.h"

size_t *getSeqPrimes_(bool *isPrime,
                      bounds const *bounds,
                      size_t numPrimes)
{
    size_t *primes = malloc(numPrimes * sizeof(size_t));

    size_t counter = 1;     // Since two is the only even prime, it is not in
    primes[0] = 2;          // isPrime and must be handled separately.

    for (size_t idx = 0; idx != bounds->upperBound; ++idx)
        if (isPrime[idx])
            primes[counter++] = idx2num_(idx);

    assert(counter == numPrimes);   // sanity check.

    return primes;
}
