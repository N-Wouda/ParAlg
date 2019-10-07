#include "utils.h"


void unmark(bool *isPrime, size_t bound, size_t from, size_t step)
{
    for (size_t number = from; number < bound; number += step)
        isPrime[number] = false;
}
