#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

#include "../primes.h"


/**
 * Initialises memory for numbers in the given half-open interval.
 *
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @return          Array of booleans over the interval, where their value
 *                  indicates prime number status.
 */
bool *init_(bounds const *bounds);

/**
 * Counts the number of primes in the given array.
 *
 * @param isPrime   Array of booleans.
 * @param bound     Size of the array.
 * @return          Number of primes.
 */
size_t countPrimes_(bool const *isPrime, size_t bound);

/**
 * Crosses-out multiples of a given prime, from a specific starting point.
 *
 * @param isPrime   Array of booleans.
 * @param bound     Size of the array.
 * @param from      Starting point in the array.
 * @param step      Step size, or multiple.
 */
void unmark_(bool *isPrime, size_t bound, size_t from, size_t step);

#endif // UTILS_H
