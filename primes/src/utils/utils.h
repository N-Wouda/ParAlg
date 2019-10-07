#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

#include "../primes.h"


bool *init(bounds const *bounds);

bounds const blockBounds(bounds const *bounds, size_t numProcs, size_t pid);

size_t countPrimes(bool const *isPrime, size_t bound);

size_t *getPrimes(bool const *isPrime, bounds const *bounds, size_t numPrimes);

void unmark(bool *isPrime, size_t bound, size_t from, size_t step);

#endif // UTILS_H
