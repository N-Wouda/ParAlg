#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"


bool *init(bounds const *bounds)
{
    size_t const size = 1 + oddCount(bounds) ;//(bounds->lowerBound == 0)
    //printf("size of isprime is %zu\n", size);
    bool *isPrime = malloc(size * sizeof(bool));

    //printf("NEW prime %zu, with value %d\n", idx2numA(size, bounds->lowerBound), isPrime[size]);
    memset(isPrime, true, size * sizeof(bool));
    //printf("at last: %d \n", isPrime[size]);
    if (bounds->lowerBound < 1)         // {0} is not prime.
        memset(isPrime, false, (1 - bounds->lowerBound) * sizeof(bool));

    // This is a bit tricky, but when lowerBound is even, isPrime[0] is hit
    // by lowerBound - 1, which is obviously outside the interval.
    if (isEven(bounds->lowerBound))
        isPrime[0] = false;

    return isPrime;
}
