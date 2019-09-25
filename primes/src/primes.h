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
 * TODO
 *
 * @param bounds
 * @param numPrimes
 * @return
 */
size_t *boundedSieve(bounds const *bounds, size_t *numPrimes);

/**
 * TODO
 *
 * @param bound         The upper bound.
 * @param numProcs      Number of processors.
 */
void bspSieve(size_t bound, size_t numProcs);

#endif //PRIMES_H
