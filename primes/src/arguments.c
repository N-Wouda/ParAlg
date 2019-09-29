#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <bsp.h>

#include "main.h"


void arguments(int argc, char **argv, bounds *bounds, size_t *numProcs)
{
    if (argc > 1)
        bounds->upperBound = strtoull(argv[1], NULL, 10);
    else
    {
        printf("Missing upper bound.");
        exit(EXIT_FAILURE);
    }

    bounds->lowerBound = 0;         // some default values.
    *numProcs = bsp_nprocs();

    int option;

    while ((option = getopt(argc, argv, "l:p:")) != -1)
    {
        switch (option)
        {
            case 'l':
                bounds->lowerBound = strtoull(optarg, NULL, 10);
                break;
            case 'p':
                *numProcs = strtoull(optarg, NULL, 10);
                break;
        }
    }
}
