#include "algorithm.h"
#include "io.h"

#include <bsp.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    bsp_init(parallel, argc, argv);

    if (!parseArguments(argc, argv))
        return EXIT_FAILURE;

    if (!ARGUMENTS.useParallel)
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

        free(segments);
        releaseMatrix(&mat);

        return status ? EXIT_SUCCESS : EXIT_FAILURE;
    }

    parallel();
    return EXIT_SUCCESS;
}
