#ifndef SEQ_H
#define SEQ_H

#include <stddef.h>
#include <stdbool.h>

#include "../primes.h"


/**
 * Counts the odd numbers in the given interval.
 *
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @return          Odd number count.
 */
size_t oddCount_(bounds const *bounds);

/**
 * Obtains the primes flagged in the isPrime array. This method is intended for
 * sequential execution, and assumes the array indexes only odd numbers.
 *
 * Note: see also the inline methods `num2idx_` and `idx2num_`.
 *
 * @param isPrime   Array of booleans.
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @param numPrimes The number of primes in the array, as determined by
 *                  `countPrimes_`.
 * @return          Array of primes, of length numPrimes.
 */
size_t *getSeqPrimes_(bool *isPrime, bounds const *bounds, size_t numPrimes);

/**
 * Inline helper method to index the isPrime representation. This method takes
 * a regular number, and returns an index.
 */
inline size_t num2idx_(size_t number)
{
    return number / 2 + 1;
}

/**
 * Inline helper method to index the isPrime representation. This method takes
 * an index, and returns a regular number.
 */
inline size_t idx2num_(size_t idx)
{
    return 2 * idx - 1;
}

#endif // SEQ_H
