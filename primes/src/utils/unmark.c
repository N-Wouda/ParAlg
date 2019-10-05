#include "utils.h"
#include <stdio.h>


//unmark(isPrime, size, number * number, number);

void unmark(bool *isPrime, size_t bound, size_t from, size_t step, size_t offset)
{
    if (step*step< offset)
    {
        from = (offset + step -1)/step*step;
    }
    else
        from = step*step;
    //printf("unmark %zu with bound %zu \n ", step, bound);
    for (size_t number = from; number < bound; number += step)
    {
        //printf("%zu\n", number);
        if (number%6==5|| number%6 == 1) isPrime[num2idxA(number, offset)] = false;
    }

}
