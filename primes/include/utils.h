#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

#include "sieve.h"


/**
 * Divides the work implied by the given bounds into fair sub-intervals, and
 * returns the sub-interval associated with the given processor ID.
 *
 * @param bounds    The overall interval, for the entire programme.
 * @param numProcs  The number of processors to be used.
 * @param pid       The processor for which to compute a sub-interal.
 * @return          Sub-interval associated with processor `pid`.
 */
bounds const blockBounds(bounds const *bounds, size_t numProcs, size_t pid);

/**
 * Initialises memory for numbers in the given half-open interval.
 *
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @return          Array of booleans over the interval, where their value
 *                  indicates prime number status.
 */
bool *init(bounds const *bounds);

/**
 * Counts the number of primes in the given array.
 *
 * @param isPrime   Array of booleans.
 * @param bound     Size of the array.
 * @return          Number of primes.
 */
size_t countPrimes(bool const *isPrime, size_t bound);

/**
 * Obtains the primes flagged in the isPrime array.
 *
 * @param isPrime   Array of booleans.
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @param numPrimes The number of primes in the array, as determined by
 *                  `countPrimes`.
 * @return          Array of primes, of length numPrimes.
 */
size_t *getPrimes(bool const *isPrime, bounds const *bounds, size_t numPrimes);

/**
 * Counts the odd numbers in the given interval.
 *
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @return          Odd number count.
 */
size_t oddCount(bounds const *bounds);

/**
 * Crosses-out multiples of a given prime, from a specific starting point.
 *
 * @param isPrime   Array of booleans.
 * @param bound     Size of the array.
 * @param from      Starting point in the array.
 * @param step      Step size, or multiple.
 */
void unmark(bool *isPrime, size_t bound, size_t from, size_t step);

/**
 * Inline helper method to determine if the argument is odd.
 */
inline bool isOdd(size_t number)
{
    return number & 1;
}

/**
 * Inline helper method to determine if the argument is even.
 */
inline bool isEven(size_t number)
{
    return !isOdd(number);
}

/**
 * Inline helper method to index the isPrime representation. This method takes
 * a regular number, and returns an index.
 */
inline size_t num2idx(size_t number, size_t offset)
{
    // This maps a number down into a reduced memory space storing only odd
    // numbers. If the offset is even, we need to add one.
    return (number - offset) / 2 + isEven(offset);
}

/**
 * Inline helper method to index the isPrime representation. This method takes
 * an index, and returns a regular number.
 */
inline size_t idx2num(size_t idx, size_t offset)
{
    // This returns a number from a reduced memory space storing only odd
    // numbers. If the offset is even, we need to subtract one.
    return 2 * idx + offset - isEven(offset);
}

#endif // UTILS_H
