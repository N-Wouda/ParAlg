#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "primes.h"
#include "utils/utils.h"
#include "seq/seq.h"


size_t *sieve(bounds const *bounds, size_t *numPrimes)
{
    assert(bounds->upperBound >= 2);            // sanity checks.
    assert(bounds->lowerBound == 0);

    // This represents all odd numbers in the given interval, *and* zero.
    struct bounds oddBounds = {0, 1 + oddCount_(bounds)};

    bool *isPrime = init_(&oddBounds);          // marks all numbers prime.

    for (size_t number = 3; number * number < bounds->upperBound; number += 2)
        if (isPrime[num2idx_(number)])
            // If this number is prime, then it is a proper divisor for any of
            // its multiples. Note that any multiples less than the square have
            // already been unmarked at this point.
            unmark_(isPrime,
                    oddBounds.upperBound,
                    num2idx_(number * number),
                    number);

    // All the uneven primes, and two (which we did not sieve above).
    *numPrimes = 1 + countPrimes_(isPrime, oddBounds.upperBound);
    size_t *result = getSeqPrimes_(isPrime, &oddBounds, *numPrimes);

    free(isPrime);

    return result;
}
