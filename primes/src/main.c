#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "primes.h"

int main()
{
    bounds bounds = {0, 100};

    bspSieve(&bounds, 4);

    return EXIT_SUCCESS;
}
