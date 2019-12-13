#include "main.h"

#include <bsp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool arguments(int argc, char **argv, char **location, size_t *numProcs)
{
    if (argc > 1)
        *location = argv[1];
    else
    {
        printf("%s: missing data location.\n", argv[0]);
        return false;
    }

    *numProcs = bsp_nprocs();  // default value.

    int option;

    while ((option = getopt(argc, argv, "p:")) != -1)
    {
        if (option == 'p')  // `p' for processors.
            *numProcs = strtoull(optarg, NULL, 10);
        // TODO switch if more than one option
    }

    return true;
}
