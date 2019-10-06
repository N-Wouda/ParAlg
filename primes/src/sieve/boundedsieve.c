#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "sieve.h"
#include "utils.h"


size_t *boundedSieve(bounds *bounds, size_t *numPrimes)
{
    bounds->lowerBound -=  (((bounds->lowerBound % 6)== 1 || (bounds->lowerBound % 6)== 5));
    bounds->upperBound -=  (((bounds->upperBound % 6)== 1 || (bounds->upperBound % 6)== 5));
    if (bounds->lowerBound <= 2)            // this is the `regular' case.
    {
        struct bounds const zeroBound = {0, bounds->upperBound};
        return sieve(&zeroBound, numPrimes);
    }
    //printf("got to here");
    assert(bounds->upperBound >= 2);        // sanity checks.
    assert(bounds->upperBound > bounds->lowerBound);

    size_t const size = oddCount(bounds) + (bounds->lowerBound>2);

    bool *isPrime = init(bounds);      // marks all numbers in bounds prime.
    // These are all primes in the candidate region [0, sqrt(upperBound)),
    // similar to the regular sequential algorithm.
    size_t numCandPrimes = 0;
    struct bounds candidateBounds = {0, sqrt(bounds->upperBound) + 1 };
    candidateBounds.upperBound += (candidateBounds.upperBound % 6 == 1) || (candidateBounds.upperBound % 6 == 5);
    size_t *candPrimes = sieve(&candidateBounds, &numCandPrimes);

    // Equipped with these primes, we unmark all their multiples within the
    // interval. Observe that we must skip two and three, the first prime at index 0 and 1,
    // as we do not store even numbers and multiples of three.
    for (size_t idx =2; idx != numCandPrimes; ++idx)
    {
        size_t const prime = candPrimes[idx];


        size_t from;
        // Unmark all multiples of the given prime in the isPrime array. We can
        // start marking off from the first multiple of the prime in isPrime,
        // or its square, if it exceeds the lower bound.
        if (5 * prime > bounds->lowerBound)
        {
            from = 5*prime;
            //printf("1. prime %zu from %zu with idx %zu \n", prime, from, num2idxA(from, bounds->lowerBound));
            unmark(isPrime, size, num2idxA(from, bounds->lowerBound), 2*prime);
            from = 7*prime;
            //printf("1. prime %zu from %zu with idx %zu \n", prime, from, num2idxA(from, bounds->lowerBound));
            unmark(isPrime, size, num2idxA(from, bounds->lowerBound), 2*prime);
        }
        else
        {
            from = bounds->lowerBound + prime - bounds->lowerBound % prime;
            while ((from % 6 != 1) && (from % 6 != 5))
            {
                from += prime;
            }
            //printf("2. prime %zu from %zu with idx %zu \n", prime, from, num2idxA(from, bounds->lowerBound));
            unmark(isPrime, size, num2idxA(from, bounds->lowerBound), 2*prime);

            from += prime;
            while ((from % 6 != 1) && (from % 6 != 5))
            {
                from += prime;
            }
            //printf("2. prime %zu from %zu with idx %zu \n", prime, from, num2idxA(from, bounds->lowerBound));
            unmark(isPrime, size, num2idxA(from, bounds->lowerBound), 2*prime);
        }


    }

    *numPrimes = countPrimes(isPrime, size)-1;
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);
    free(candPrimes);

    return result;
}
