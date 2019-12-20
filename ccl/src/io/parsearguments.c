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
    ARGUMENTS.numProcs = bsp_nprocs();  // default value.

    int option;

    while ((option = getopt(argc, argv, "p:")) != -1)
    {
        if (option == 'p')  // `p' for processors.
            ARGUMENTS.numProcs = strtoull(optarg, NULL, 10);
    }

    return true;
}
