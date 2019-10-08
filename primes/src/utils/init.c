#include <stdlib.h>
#include <string.h>

#include "utils.h"


bool *init(bounds const *bounds)
{
    size_t const size = 1 + candidateCount(bounds);

    bool *isPrime = malloc(size * sizeof(bool));

    // Initially mark all candidates as prime.
    memset(isPrime, true, size * sizeof(bool));
    isPrime[0] = false;                        // we skip over this index.

    return isPrime;
}
