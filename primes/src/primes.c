#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "primes.h"


int main()
{
    size_t numPrimes = 0;
    bounds bounds = {0, 1000};

    size_t const *primes = sieve(&bounds, &numPrimes);

    for (size_t idx = 0; idx != numPrimes; ++idx)
        printf("%zu\n", primes[idx]);

    printf("Total number of primes: %zu\n", numPrimes);

    return EXIT_SUCCESS;
}
