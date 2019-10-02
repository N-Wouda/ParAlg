#include <stdlib.h>

#include <bsp.h>

#include "main.h"


int main(int argc, char **argv)
{
    bounds bounds;
    size_t numProcs;

    if (!arguments(argc, argv, &bounds, &numProcs))
        return EXIT_FAILURE;

    BSP_BOUNDS = &bounds;
    BSP_NUM_PROCS = numProcs;

    bsp_init(bspSieve, argc, argv);

    bspSieve();

    return EXIT_SUCCESS;
}
