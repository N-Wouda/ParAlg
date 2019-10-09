#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "sieve.h"
#include "utils.h"


size_t *sieve(bounds const *bounds, size_t *numPrimes)
{
    assert(bounds->upperBound >= 2);            // sanity checks.
    assert(bounds->lowerBound == 0);

    // This represents all candidates in the given interval. We skip over
    // index zero, so we reserve a little extra space.
    size_t const size = 1 + candidateCount(bounds);

    bool *isPrime = init(bounds);          // marks all numbers prime.

    for (size_t idx = 1, number = idx2num(idx, 0);
         number * number < bounds->upperBound;
         ++idx, number = idx2num(idx, 0))
    {
        if (isPrime[num2idx(number, 0)])
        {
            // If this number is prime, then it is a proper divisor for any of
            // its multiples. Here we know that any prime number is of the form
            // 6k +- 1, and thus its next multiple having the same remainder
            // (mod 6) is 4 * number (for mod 6 == 5), respectively 6 * number
            // (for mod 6 == 1) integers ahead. This works out to 5 * number,
            // respectively 7 * number. For a stride, we observe there are
            // 2 * number integers of the form 6k +- 1 between each successive
            // number of this form.

            // TODO start from number * number
            unmark(isPrime,
                   size,
                   num2idx(5 * number, bounds->lowerBound),
                   2 * number);

            unmark(isPrime,
                   size,
                   num2idx(7 * number, bounds->lowerBound),
                   2 * number);
        }
    }

    // All the primes, plus two and three (which we did not sieve above).
    *numPrimes = 2 + countPrimes(isPrime, size);
    size_t *result = getPrimes(isPrime, bounds, *numPrimes);

    free(isPrime);

    return result;
}
