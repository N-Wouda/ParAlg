#include "utils.h"
#include <stdio.h>


//unmark(isPrime, size, number * number, number);

void unmark(bool *isPrime, size_t bound, size_t from, size_t step)
{
    for (size_t idx = from; idx < bound; idx += step)
    {
        isPrime[idx] = false;
        //printf("delete %zu which is %zu\n", idx, idx2numA(idx, 200));
    }

}
