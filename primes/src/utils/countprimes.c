#include "utils.h"


size_t countPrimes_(bool const *isPrime, size_t bound)
{
    size_t count = 0;

    for (size_t idx = 0; idx != bound; ++idx)
        count += isPrime[idx];

    return count;
}
