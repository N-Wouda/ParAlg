#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sieve.h"
#include "utils.h"


size_t *sieve(bounds const *bounds, size_t *numPrimes)
{
    assert(bounds->upperBound >= 2);            // sanity checks.
    assert(bounds->lowerBound == 0);

    // This represents all odd numbers in the given interval, *and* two.
    size_t const size = 1 + oddCount(bounds);

    bool *isPrime = init(bounds);          // marks all numbers prime.

    int idA;
    size_t number = 5;
    for (idA=1 ; number*number < bounds->upperBound; idA += 1) //number*number < bounds->upperBound
    {

        //printf("id: %d", idA);
        //printf("here");
        //printf("id: %d\n", idA);


        //printf("id: %d with number: %zu \n", idA, number);
        //printf("here");
        //printf("id: %d with number:  \n", idA);
        if (isPrime[num2idxA(number, 0)])
        {
            //printf("prime!");
            // If this number is prime, then it is a proper divisor for any of
            // its multiples. Note that any multiples less than the square have
            // already been unmarked at this point.
            unmark(isPrime, bounds->upperBound, number*number, number,0);
        }
        number = ((idA + 2)/2*6 - 2*((idA+1)%2) + 1);
    }


    // All the odd primes, and two (which we did not sieve above).
    *numPrimes = 1 + countPrimes(isPrime, size);
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);

    return result;
}
