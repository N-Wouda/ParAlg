#ifndef PRIMES_H
#define PRIMES_H

#include <stddef.h>

typedef struct bounds {
    size_t lowerBound;
    size_t upperBound;
} bounds;


/**
 * Sieves prime numbers below the specified bound (exclusive). Assumes the
 * specified bound is greater than or equal to least 2.
 *
 * @param bounds        The upper bound. Only the upperBound variable is used,
 *                      lowerBound is assumed zero.
 * @param numPrimes     After this function returns, numPrimes contains the
 *                      number of primes in the returned array.
 * @return              Array of primes, of length numPrimes.
 */
size_t *sieve(bounds const *bounds, size_t *numPrimes);

/**
 * Sieves prime numbers in the specified interval bounds. Assumes the
 * specified upperBound is greater than or equal to at least two, and
 * upperBound > lowerBound.
 *
 * Note: cf. function `sieve`.
 *
 * @param bounds        The half-open interval [lowerBound, upperBound).
 * @param numPrimes     After this function returns, numPrimes contains the
 *                      number of primes in the returned array.
 * @return              Array of primes, of length numPrimes.
 */
size_t *boundedSieve(bounds const *bounds, size_t *numPrimes);

/**
 * Bulk synchronous parallel implementation of the prime number sieve. TODO
 *
 * @param bounds         The upper bound.
 * @param numProcs      Number of processors.
 */
void bspSieve(bounds const *bounds, size_t numProcs);

#endif //PRIMES_H
