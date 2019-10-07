#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
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

size_t sixkCount(size_t upperBound);

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
 * an index, and returns a regular number.
 */
inline size_t idx2num(size_t idx, size_t offset)
{
    // This returns a number from a reduced memory space storing only numbers
    // of the form 6k +-1. If the offset falls between 6k+1 and 6k-1, we need to
    // turn the order of + - around.
    if (offset == 0) return ((idx + 1) / 2 * 6 - 2 * (idx % 2) + 1);
    size_t kOffsetOdds = ((offset % 6) == 0 || (offset % 6) == 5);
    size_t kOffset = (offset + 1) / 6;
    size_t k = ((idx + 1 + kOffsetOdds)/2 + kOffset - kOffsetOdds);

    // plusMinus is 0 for 6k +1 and 1 for 6k -1.
    size_t plusMinus = ((idx + kOffsetOdds) % 2);
    return (k * 6 - 2 * plusMinus + 1);
}

/**
 * Inline helper method to index the isPrime representation. This method takes
 * a regular number, and returns an index.
 */
inline size_t num2idx(size_t number, size_t offset)
{
    // This maps a number down into a reduced memory space storing only numbers
    // of the form 6k+-1. For every k there are two places in the list.
    // minusOne is one for numbers of the form 6k-1 and zero for 6k+1.

    size_t minusOne = number % 6 == 5;
    size_t skip = sixkCount(offset) + ((offset % 6 == 5) || (offset % 6 == 1));
    size_t k = (number + 1) / 6;
    return (k * 2 -  minusOne) - skip;
}


#endif // UTILS_H
