#include <stdlib.h>
#include <assert.h>

#include "utils.h"
#include "bsp.h"

#include <stdio.h>

size_t *getPrimes(bool const *isPrime, bounds const *bounds, size_t numPrimes)
{

    size_t size = oddCount(bounds) + (bounds->lowerBound>2);     // regular size of isPrime

    size_t counter = 0;

//    if (size == 0)                      // there are no numbers in this
//        return NULL;                    // interval, let alone primes.
//    printf("last size: %zu\n", size);
    size_t *primes = malloc(numPrimes * sizeof(size_t));

    if (bounds->lowerBound <= 2)        // Since two is the only even prime,
    {                                   // it is not regularly in isPrime and
        primes[0] = 2;                  // must be handled separately.
        counter++;
        size++;
        primes[1] = 3;
        counter++;
        size++;
    }

    for (size_t idx = 0; idx != size; ++idx)
    {
        //printf("prime at %zu:  %zu, value:  ", idx, idx2numA(idx, bounds->lowerBound));
        if (isPrime[idx])
        {
            //printf("real prime at %zu:  %zu ", idx, idx2numA(idx, bounds->lowerBound));
            primes[counter++] = idx2numA(idx, bounds->lowerBound);

        }
    }

    //printf("new prime %zu, with value %d\n", idx2numA(3, bounds->lowerBound), isPrime[3]);
    //printf("\nPID %zu found numprimes: %d and counter: %zu\n", bsp_pid(),numPrimes, counter);


    for (size_t alexC = 0; alexC< numPrimes; alexC++)
    {
        printf("proc %zu found: %zu\n", bsp_pid(),primes[alexC]);
    }
    assert(counter == numPrimes);       // sanity check.

    return primes;
}
