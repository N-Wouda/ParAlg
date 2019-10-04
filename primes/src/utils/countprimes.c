#include "utils.h"


size_t countPrimes(bool const *isPrime, size_t bound)
{
    size_t count = 1;

    for (size_t idx = 0; idx != bound; ++idx)
        count += isPrime[idx];

    return count;
}
