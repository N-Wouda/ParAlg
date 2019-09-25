#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "primes.h"

int main()
{
    size_t numPrimes = 0;
    bounds bounds = {900, 1000};

    size_t *primes = boundedSieve(&bounds, &numPrimes);

    for (size_t idx = 0; idx != numPrimes; ++idx)
        printf("%zu\n", primes[idx]);

    printf("Total number of primes: %zu\n", numPrimes);

    free(primes);

    return EXIT_SUCCESS;
}
