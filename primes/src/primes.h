#ifndef PRIMES_H
#define PRIMES_H

#include <stddef.h>


typedef struct bounds
{
    size_t lowerBound;
    size_t upperBound;
} bounds;

/**
 * Sieves prime numbers between the lowerBound and upperBound specified via the
 * bounds parameter. The interval is [lowerBound, upperBound).
 *
 * @param bounds    The lower and upper bound, as a struct.
 * @param numPrimes After this function returns,numPrimes contains the number
 *                  of primes in the returned array.
 * @return          Array of primes, of length numPrimes.
 */
size_t *sieve(bounds const *bounds, size_t *numPrimes);

#endif // PRIMES_H
