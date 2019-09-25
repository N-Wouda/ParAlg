#include <stdlib.h>
#include <string.h>

#include "utils.h"


bool *init_(size_t bound)
{
    bool *isPrime = malloc(bound * sizeof(bool));

    memset(isPrime, true, bound * sizeof(bool));
    memset(isPrime, false, 2 * sizeof(bool));   // {0, 1} are not prime.

    return isPrime;
}
