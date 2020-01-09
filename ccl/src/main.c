#include "algorithm.h"
#include "io.h"

#include <bsp.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    bsp_init(parallel, argc, argv);

    if (!parseArguments(argc, argv))
        return EXIT_FAILURE;

    if (ARGUMENTS.useParallel)
        parallel();
    else
    {
        bool status = true;

        matrix mat = readMatrix(ARGUMENTS.inLocation, &status);

        if (!status)
            return EXIT_FAILURE;

        size_t numSegments;
        segment *segments = sequential(&mat, &numSegments);

        writeSegments(ARGUMENTS.outLocation,
                      segments,
                      numSegments,
                      mat.length,
                      &status);

        if (!status)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
