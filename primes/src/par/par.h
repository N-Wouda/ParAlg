#ifndef PAR_H
#define PAR_H

#include <stddef.h>
#include <stdbool.h>

#include "../primes.h"


/**
 * Obtains the primes flagged in the isPrime array. This method is intended
 * for parallel execution, and does not assume a special structure on the
 * array.
 *
 * @param isPrime   Array of booleans.
 * @param bounds    The half-open interval [lowerBound, upperBound).
 * @param numPrimes The number of primes in the array, as determined by
 *                  `countPrimes_`.
 * @return          Array of primes, of length numPrimes.
 */
size_t *getParPrimes_(bool const *isPrime,
                      bounds const *bounds,
                      size_t numPrimes);

#endif // PAR_H
