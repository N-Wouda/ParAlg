#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

#include "../primes.h"


bool *init_(size_t bound);

size_t countPrimes_(bool const *isPrime, size_t bound);

size_t *getPrimes_(bool const *isPrime, bounds const *bounds, size_t numPrimes);

void unmark_(bool *isPrime, size_t bound, size_t from, size_t step);

#endif // UTILS_H
