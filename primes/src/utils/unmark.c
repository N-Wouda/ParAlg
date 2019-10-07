#include "utils.h"
#include <stdio.h>


void unmark(bool *isPrime, size_t bound, size_t from, size_t step)
{
    for (size_t idx = from; idx < bound; idx += step)
        isPrime[idx] = false;
}
