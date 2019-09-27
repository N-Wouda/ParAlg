#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <bsp/bsp.h>
#include <assert.h>

#include "primes.h"

long BSP_NUM_PROCS_;
bounds const *BSP_BOUNDS_;

int main(int argc, char **argv)
{
    bsp_init(bspSieve, argc, argv);
    bounds bounds;
    if (argc > 1)
    {
        size_t upperBound = (size_t) atol(argv[1]);
        bounds = (struct bounds) {0, upperBound};
        BSP_BOUNDS_ = &bounds;
    }
    else
    {
        printf("Argument n not supplied\n");
        return EXIT_FAILURE;
    }

    if (argc > 2)
        BSP_NUM_PROCS_ = atol(argv[2]);
    else
        BSP_NUM_PROCS_ = bsp_nprocs();



    bspSieve();



    return EXIT_SUCCESS;
}

