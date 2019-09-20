#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "primes.h"


bool *init(size_t bound);

size_t countPrimes(bool const *isPrime, size_t bound);

size_t *getPrimes(bool const *isPrime, size_t bound, size_t numPrimes);

void unmark(bool *isPrime, size_t bound, size_t from, size_t step);

size_t *sieve(size_t bound, size_t *numPrimes)
{
    assert(bound >= 2);             // sanity check.

    // Initially mark all numbers as primes using a helper array.
    bool *isPrime = init(bound);

    for (size_t number = 2; number * number < bound; ++number)
    {
        if (isPrime[number])
            // If this number is prime, then it is a proper divisor for any of
            // its multiples. Note that any multiples less than the square have
            // already been unmarked at this point.
            unmark(isPrime, bound, number * number, number);
    }

    *numPrimes = countPrimes(isPrime, bound);
    size_t *result = getPrimes(isPrime, bound, *numPrimes);

    free(isPrime);      // clean-up helper array.

    return result;
}

bool *init(size_t bound)
{
    bool *isPrime = malloc(bound * sizeof(bool));

    memset(isPrime, true, bound * sizeof(bool));
    memset(isPrime, false, 2 * sizeof(bool));   // {0, 1} are not prime.

    return isPrime;
}

size_t countPrimes(bool const *isPrime, size_t bound)
{
    size_t count = 0;

    for (size_t idx = 0; idx != bound; ++idx)
        count += isPrime[idx];

    return count;
}

size_t *getPrimes(bool const *isPrime, size_t bound, size_t numPrimes)
{
    size_t *primes = malloc(numPrimes * sizeof(size_t));
    size_t counter = 0;

    // Identifies the primes and inserts them into the primes list.
    for (size_t number = 0; number != bound; ++number)
    {
        if (isPrime[number])
            primes[counter++] = number;
    }

    assert(counter == numPrimes);   // sanity check.

    return primes;
}

void unmark(bool *isPrime, size_t bound, size_t from, size_t step)
{
    for (size_t number = from; number < bound; number += step)
        isPrime[number] = false;
}
