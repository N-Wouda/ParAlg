#include "main.h"

#include "segment.h"
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

    getSegments(mat);

    free(mat.x);
    free(mat.y);
    free(mat.z);

    return EXIT_SUCCESS;
}
