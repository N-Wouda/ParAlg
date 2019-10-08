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
 * Counts numbers of the form 6k +- 1 in the given interval. This may be used
 * to determine the size of the isPrime array.
 *
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @return          Number count.
 */
size_t candidateCount(bounds const *bounds);

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
 * Inline helper method to index the isPrime representation. This method takes
 * an index, and returns a regular number.
 *
 * See also function num2idx.
 */
inline size_t idx2num(size_t idx, size_t offset)
{
    // This returns a number from a reduced memory space storing only numbers
    // of the form 6k +- 1.
    if (offset == 0)    // this is the regular case.
        return (idx + 1) / 2 * 6 - 2 * (idx % 2) + 1;

    bool const kOffsetOdds = (offset % 6) == 0 || (offset % 6) == 5;
    size_t const kOffset = (offset + 1) / 6;

    size_t const k = (idx + 1 + kOffsetOdds) / 2 + kOffset - kOffsetOdds;

    // The modulo part here determines whether we deal with a number 6k - 1,
    // or 6k + 1. See also num2idx.
    return 6 * k - 2 * ((idx + kOffsetOdds) % 2) + 1;
}

/**
 * Inline helper method to index the isPrime representation. This method takes
 * a regular number, and returns an index.
 *
 * See also function idx2num.
 */
inline size_t num2idx(size_t number, size_t offset)
{
    // This maps a number down into a reduced memory space storing only numbers
    // of the form 6k +- 1.
    bounds const bounds = {0, offset};

    size_t const skip = candidateCount(&bounds)
        + ((offset % 6 == 5) || (offset % 6 == 1));

    size_t const k = (number + 1) / 6;

    // For each candidate around 6k, we have an index into the isPrime array.
    // 6k + 1 is stored at 2k (minus some skips due to the offset), whereas
    // 6k - 1 is stored at 2k - 1 (again the same about the offsets). Which
    // number we face here is easily determined, as 6k - 1 mod 6 == 5.
    return 2 * k - (number % 6 == 5) - skip;
}

#endif // UTILS_H
