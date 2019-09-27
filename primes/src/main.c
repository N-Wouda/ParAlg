#include <stdlib.h>
#include <stdio.h>

#include "primes.h"


int main()
{
    bounds const bounds = {0, 100};

    size_t numPrimes = 0;
    size_t *primes = boundedSieve(&bounds, &numPrimes);

    for (size_t idx = 0; idx != numPrimes; ++idx)
        printf("Prime %zu\n", primes[idx]);

    printf("Number of primes %zu", numPrimes);

    free(primes);

    return EXIT_SUCCESS;
}
