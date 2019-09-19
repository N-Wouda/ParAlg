#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "primes.h"


bool *init(bounds const *bounds);

size_t countPrimes(bool const *isPrime, size_t bound);

size_t *getPrimes(bool const *isPrime, size_t bound, size_t numPrimes);

/**
 * Sieves prime numbers between the lowerBound and upperBound specified via the
 * bounds parameter. The interval is [lowerBound, upperBound).
 * 
 * @param bounds    The lower and upper bound, as a struct.
 * @param numPrimes After this function returns,numPrimes contains the number
 *                  of primes in the returned array.
 * @return          Array of primes, of length numPrimes.
 */
size_t *sieve(bounds const *bounds, size_t *numPrimes)
{
    // TODO: Parallel sieving probably requires us to consider a sieving method
    // TODO: that respects both bounds.
    // Initially set all numbers to primes using a helper array.
    bool *isPrime = init(bounds);

    // TODO: this also sieves even numbers, but we can probably optimise those
    // TODO: away (and multiples of low primes, say, {3, 5, 7, 9}).
    for (size_t number = 2; number * number <= bounds->upperBound; ++number)
    {
        if (isPrime[number])
        {
            // If this number is prime, then any multiple beyond its square
            // divides by itself. Note that any multiples less than the square
            // have already been marked at this point.
            for (size_t multiple = number * number;
                 multiple <= bounds->upperBound;
                 multiple += number)
            {
                isPrime[multiple] = false;
            }
        }
    }

    *numPrimes = countPrimes(isPrime, bounds->upperBound);
    size_t *result = getPrimes(isPrime, bounds->upperBound, *numPrimes);

    free(isPrime);      // clean-up helper array.

    return result;
}

inline bool *init(bounds const *bounds)
{
    bool *isPrime = malloc(bounds->upperBound * sizeof(bool));

    memset(isPrime, true, bounds->upperBound * sizeof(bool));
    memset(isPrime, false, 2 * sizeof(bool));   // {0, 1} are not prime.

    return isPrime;
}

inline size_t countPrimes(bool const *isPrime, size_t bound)
{
    size_t count = 0;

    for (size_t idx = 0; idx != bound; ++idx)
        count += isPrime[idx];

    return count;
}

inline size_t *getPrimes(bool const *isPrime, size_t bound, size_t numPrimes)
{
    size_t *primes = malloc(numPrimes * sizeof(size_t));
    size_t counter = 0;

    // Identifies the primes and inserts them into the primes list.
    for (size_t number = 0; number != bound; ++number)
    {
        if (isPrime[number])
            primes[counter++] = number;
    }

    assert(counter == numPrimes);  // sanity check.

    return primes;
}
