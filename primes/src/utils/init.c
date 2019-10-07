#include <stdlib.h>
#include <string.h>

#include "utils.h"


bool *init(bounds const *bounds)
{
    size_t const range = bounds->upperBound - bounds->lowerBound;

    bool *isPrime = malloc(range * sizeof(bool));

    memset(isPrime, true, range * sizeof(bool));

    if (bounds->lowerBound < 2)        // {0, 1} are not prime.
        memset(isPrime, false, (2 - bounds->lowerBound) * sizeof(bool));

    return isPrime;
}
