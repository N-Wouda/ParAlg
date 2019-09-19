#ifndef PRIMES_H
#define PRIMES_H

#include <stddef.h>


typedef struct bounds
{
    size_t lowerBound;
    size_t upperBound;
} bounds;

size_t *sieve(bounds const *bounds, size_t *numPrimes);

#endif // PRIMES_H
