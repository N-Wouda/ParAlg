#include <stdlib.h>

#include "main.h"


int main(int argc, char **argv)
{
    bounds bounds;
    size_t numProcs;

    arguments(argc, argv, &bounds, &numProcs);

    bspSieve(&bounds, numProcs);

    return EXIT_SUCCESS;
}
