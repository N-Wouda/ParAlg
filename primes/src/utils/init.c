#include <stdlib.h>
#include <string.h>

#include "utils.h"


bool *init(bounds const *bounds)
{
    size_t const size = 1 + candidateCount(bounds) ;

    bool *isPrime = malloc(size * sizeof(bool));

    memset(isPrime, true, size * sizeof(bool));
    isPrime[0] = false;

    return isPrime;
}
