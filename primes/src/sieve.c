#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "primes.h"

// Forward declarations for helper methods.
size_t countPrimes(bool const *isPrime, size_t bound);
size_t *getPrimes(bool const *isPrime, size_t bound, size_t numPrimes);


// TODO: Parallel sieving probably requires us to consider a sieving method
// TODO: that respects both bounds.
size_t *sieve(struct bounds const *bounds, size_t *numPrimes)
{
    // Initially set all numbers to primes using a helper array.
    bool *isPrime = malloc((bounds->upperBound + 1) * sizeof(bool));
    memset(isPrime, true, (bounds->upperBound + 1) * sizeof(bool));

    // TODO: this also sieves even numbers, but we can probably optimise those
    // TODO: away (and multiples of low primes, say, {3, 5, 7, 9}).
    for (size_t number = 2; number * number <= bounds->upperBound; ++number)
    {
        if (isPrime[number])
        {
            // If this number is a prime, then its square divides by itself and
            // so do any next multiple below the bound. Note that any multiples
            // below the square have already been marked at this point.
            for (size_t offset = number * number; offset <= bounds->upperBound;
                 offset += number)
                isPrime[offset] = false;
        }
    }

    *numPrimes = countPrimes(isPrime, bounds->upperBound + 1);
    size_t *result = getPrimes(isPrime, bounds->upperBound, *numPrimes);

    free(isPrime);      // clean-up helper array

    return result;
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
    size_t *primes = malloc((bound + 1) * sizeof(size_t));
    size_t counter = 0;

    // Identifies the primes and inserts them into the primes list
    for (size_t number = 0; number != bound; ++number)
    {
        if (isPrime[number])
            primes[counter++] = number;
    }

    assert(counter == numPrimes);  // sanity check

    return primes;
}
