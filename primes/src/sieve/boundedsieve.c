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
    //shift the bounds if they fall on numbers of the form 6k+-1.
    // Note that if this is the case that shifting the interval one place to the
    // left that the new interval will contain the same primes.
    bounds->lowerBound -=  (((bounds->lowerBound % 6)== 1
        || (bounds->lowerBound % 6)== 5));
    bounds->upperBound -=  (((bounds->upperBound % 6)== 1
        || (bounds->upperBound % 6)== 5));

    if (bounds->lowerBound <= 2)            // this is the `regular' case.
    {
        struct bounds const zeroBound = {0, bounds->upperBound};
        return sieve(&zeroBound, numPrimes);
    }

    assert(bounds->upperBound >= 2);        // sanity checks.
    assert(bounds->upperBound > bounds->lowerBound);

    size_t const size = oddCount(bounds) + (bounds->lowerBound>2);

    bool *isPrime = init(bounds);      // marks all numbers in bounds prime.

    // These are all primes in the candidate region [0, sqrt(upperBound)),
    // similar to the regular sequential algorithm.
    size_t numCandPrimes = 0;
    struct bounds candidateBounds =
        {0, sqrt(bounds->upperBound) + 1 };
    candidateBounds.upperBound += (candidateBounds.upperBound % 6 == 1)
        || (candidateBounds.upperBound % 6 == 5);
    size_t *candPrimes = sieve(&candidateBounds, &numCandPrimes);

    // Equipped with these primes, we unmark all their multiples within the
    // interval. Observe that we must skip two and three, the first primes at
    // index 0 and 1 as we do not store even numbers and multiples of three.
    // We unmark all multiples which are of the form 6k-1 and 6k+1 separately
    // because each has a fixed number of values in numPrimes in between, namely
    // 6 times the prime.
    for (size_t idx =2; idx != numCandPrimes; ++idx)
    {
        size_t const prime = candPrimes[idx];
        size_t from;

        // Unmark all multiples of the given prime in the isPrime array. We can
        // start marking off from the first multiple of the prime in isPrime.
        if (5 * prime > bounds->lowerBound)
        {
            from = 5*prime;
            unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2*prime);
            from = 7*prime;
            unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2*prime);
        }
        else
        {
            // from is the first multiple of the prime larger than the
            // lowerbound and the while loop continues until it finds the first
            // multiple in numPrimes.
            from = bounds->lowerBound + prime - bounds->lowerBound % prime;
            while ((from % 6 != 1) && (from % 6 != 5)) from += prime;
            unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2*prime);

            from += prime;
            while ((from % 6 != 1) && (from % 6 != 5)) from += prime;
            unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2*prime);
        }


    }

    *numPrimes = countPrimes(isPrime, size)-1;
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);
    free(candPrimes);

    return result;
}
