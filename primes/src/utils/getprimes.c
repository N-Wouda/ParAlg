#include <stdlib.h>
#include <assert.h>

#include "utils.h"
#include "bsp.h"

#include <stdio.h>

size_t *getPrimes(bool const *isPrime, bounds const *bounds, size_t numPrimes)
{

    size_t size = oddCount(bounds) + (bounds->lowerBound>2) - (bounds->lowerBound<=3); // size of isPrime

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

    for (size_t idx = 2; idx < size; idx += 2)
    {
        if (isPrime[idx] && isPrime[idx -1])
        {
            primes[counter++] = idx2num(idx-1, bounds->lowerBound);
            primes[counter++] = idx2num(idx, bounds->lowerBound);
        }
    }

    numPrimes = counter; //TODO: wordt numPrimes hier aangepast? of alleen lokaal?

//    for (size_t alexC = 0; alexC< numPrimes; alexC++)
//    {
//        printf("proc %d found: %zu\n", bsp_pid(),primes[alexC]);
//    }

    return primes;
}
