#include "io.h"

#include <bsp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

arguments ARGUMENTS;


bool parseArguments(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("%s: missing data location(s).\n", argv[0]);
        return false;
    }

    ARGUMENTS.inLocation = argv[1];
    ARGUMENTS.outLocation = argv[2];

    ARGUMENTS.numProcs = bsp_nprocs();  // default values.
    ARGUMENTS.useParallel = true;

    int option;

    while ((option = getopt(argc, argv, "p:s")) != -1)
    {
        switch (option)
        {
            case 'p':
                ARGUMENTS.numProcs = strtoull(optarg, NULL, 10);
                break;
            case 's':
                ARGUMENTS.useParallel = false;
                break;
            default:
                return false;
        }
    }

    return true;
}
