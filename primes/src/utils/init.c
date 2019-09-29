#include <stdlib.h>
#include <string.h>

#include "utils.h"


bool *init(bounds const *bounds)
{
    size_t const size = (bounds->lowerBound == 0) + oddCount(bounds);

    bool *isPrime = malloc(size * sizeof(bool));

    memset(isPrime, true, size * sizeof(bool));

    if (bounds->lowerBound < 2)         // {0, 1} are not prime.
        memset(isPrime, false, (2 - bounds->lowerBound) * sizeof(bool));

    // This is a bit tricky, but when lowerBound is even, isPrime[0] is hit
    // by lowerBound - 1, which is obviously outside the interval.
    if (bounds->lowerBound % 2 == 0)
        isPrime[0] = false;

    return isPrime;
}
