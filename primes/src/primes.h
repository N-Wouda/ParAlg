#ifndef PRIMES_H
#define PRIMES_H

#include <stddef.h>


struct bounds {
    size_t lowerBound;
    size_t upperBound;
};

size_t *sieve(struct bounds const *bounds, size_t *numPrimes);

#endif // PRIMES_H
