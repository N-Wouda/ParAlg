#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include <bsp.h>

#include "main.h"


long BSP_NUM_PROCS;
bounds const *BSP_BOUNDS;

int main(int argc, char **argv)
{
    bsp_init(bspSieve, argc, argv);

    bounds bounds;
    size_t numProcs;

    if (!arguments(argc, argv, &bounds, &numProcs))
        return EXIT_FAILURE;

    assert(numProcs > 0);       // sanity check.

    BSP_BOUNDS = &bounds;
    BSP_NUM_PROCS = numProcs;


    bspSieve();

    return EXIT_SUCCESS;
}
