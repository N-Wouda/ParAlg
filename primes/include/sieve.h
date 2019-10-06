#ifndef SIEVE_H
#define SIEVE_H

#include <stddef.h>


typedef struct bounds {     // Sieve bounds, as a half-open interval.
    size_t lowerBound;
    size_t upperBound;
} bounds;

bounds const *BSP_BOUNDS;   // Bounds for the parallel sieve.
size_t BSP_NUM_PROCS;       // Number of processors to use.

/**
 * Sieves prime numbers below the specified bound (exclusive). The specified
 * upperBound must be greater than or equal to least 2.
 *
 * @param bounds        The upper bound. Only the upperBound variable is used,
 *                      lowerBound must be zero.
 * @param numPrimes     After this function returns, numPrimes contains the
 *                      number of primes in the returned array.
 * @return              Array of primes, of length numPrimes.
 */
size_t *sieve(bounds const *bounds, size_t *numPrimes);

/**
 * Sieves prime numbers in the specified interval bounds. The specified
 * upperBound must be greater than or equal to at least two, and
 * upperBound > lowerBound.
 *
 * Note: see also function `sieve`.
 *
 * @param bounds        The half-open interval [lowerBound, upperBound).
 * @param numPrimes     After this function returns, numPrimes contains the
 *                      number of primes in the returned array.
 * @return              Array of primes, of length numPrimes.
 */
size_t *boundedSieve(bounds *bounds, size_t *numPrimes);

/**
 * Bulk synchronous parallel implementation of the prime number sieve. Uses a
 * block distribution over the number of processors (program argument), and the
 * bounded sieve.
 *
 * Note: see also function `boundedSieve`.
 */
void bspSieve();

#endif // SIEVE_H
