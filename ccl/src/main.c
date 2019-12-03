#include "main.h"

#include "sparse.h"

#include <stdlib.h>


int main(int argc, char **argv)
{
    char *location;
    size_t numProcs;

    if (!arguments(argc, argv, &location, &numProcs))
        return EXIT_FAILURE;

    bool status = true;
    matrix_t mat = readMatrix(location, &status);

    if (!status)
        return EXIT_FAILURE;

    // TODO

    return EXIT_SUCCESS;
}
