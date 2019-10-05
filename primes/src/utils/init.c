#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"


bool *init(bounds const *bounds)
{
    size_t const size = 1 + oddCount(bounds) ;//(bounds->lowerBound == 0)

    bool *isPrime = malloc(size * sizeof(bool));


    memset(isPrime, true, size * sizeof(bool));
    isPrime[0] = false;
    //printf("NEW prime %zu, with value %d\n size of isprime is %zu\n", idx2numA(0, bounds->lowerBound), isPrime[0],size);
    //printf("size of isprime is %zu\n", size);
    //printf("at last: %d \n", isPrime[size-1]);
    if (bounds->lowerBound < 1)         // {0} is not prime.
        memset(isPrime, false,  sizeof(bool));

    // This is a bit tricky, but when lowerBound is even, isPrime[0] is hit
    // by lowerBound - 1, which is obviously outside the interval.
    if (isEven(bounds->lowerBound))
        isPrime[0] = false;

    return isPrime;
}
