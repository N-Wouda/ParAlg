#include "algorithm.h"
#include "io.h"

#include <bsp.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    bsp_init(parallel, argc, argv);

    if (!parseArguments(argc, argv))
        return EXIT_FAILURE;

    parallel();

    return EXIT_SUCCESS;
}
