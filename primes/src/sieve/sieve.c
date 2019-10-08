#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "sieve.h"
#include "utils.h"


size_t *sieve(bounds const *bounds, size_t *numPrimes, size_t twins)
{
    assert(bounds->upperBound >= 2);            // sanity checks.
    assert(bounds->lowerBound == 0);

    // This represents all 6k+-1 numbers in the given interval, and two, three.
    size_t const size = 1 + oddCount(bounds);

    bool *isPrime = init(bounds);          // marks all numbers prime.

    int idA;
    size_t number = 5;
    for (idA=1 ; number*number < bounds->upperBound; idA += 1)
    {

        if (isPrime[num2idx(number, 0)])
        {
            // If this number is prime, then it is a proper divisor for any of
            // its multiples. Note that any multiples less than the square have
            // already been unmarked at this point.

            size_t from = 5*number;
            unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2*number);
            from = 7*number;
            unmark(isPrime, size, num2idx(from, bounds->lowerBound), 2*number);
        }
        number = idx2num(idA + 1,0);
    }

    // All the primes, and two (which we did not sieve above).
    *numPrimes = 1 + countPrimes(isPrime, size);
    size_t *result = twins
        ? getTwinPrimes(isPrime, bounds, *numPrimes)
        : getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);

    return result;
}
