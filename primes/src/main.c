#include <stdlib.h>
#include <assert.h>

#include <bsp.h>

#include "main.h"


int main(int argc, char **argv)
{
    bounds bounds;
    size_t numProcs;

    if (!arguments(argc, argv, &bounds, &numProcs))
        return EXIT_FAILURE;

    assert(numProcs > 0);       // sanity check.

    BSP_BOUNDS = &bounds;
    BSP_NUM_PROCS = numProcs;

    bsp_init(bspSieve, argc, argv);

    bspSieve();

    return EXIT_SUCCESS;
}
