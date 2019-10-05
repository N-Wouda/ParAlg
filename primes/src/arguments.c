#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <bsp.h>

#include "main.h"


bool arguments(int argc, char **argv, bounds *bounds, size_t *numProcs)
{
    if (argc > 1)
        bounds->upperBound = strtoull(argv[1], NULL, 10);
    else
    {
        printf("%s: missing upper bound.\n", argv[0]);
        return false;
    }

    bounds->lowerBound = 0;         // some default values.
    *numProcs = bsp_nprocs();

    int option;

    while ((option = getopt(argc, argv, "l:p:")) != -1)
    {
        switch (option)
        {
            case 'l':       // `l' for lowerBound.
                bounds->lowerBound = strtoull(optarg, NULL, 10);
                break;
            case 'p':       // `p' for processors.
                *numProcs = strtoull(optarg, NULL, 10);
                break;
        }
    }

    return true;
}
