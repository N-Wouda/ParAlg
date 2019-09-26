#include <stdlib.h>

#include "primes.h"

int main()
{
    bounds const bounds = {0, 50};

    bspSieve(&bounds, 4);

    return EXIT_SUCCESS;
}
