#include "main.h"

#include "component.h"
#include "io.h"
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
    matrix const mat = readMatrix(location, &status);

    if (!status)
        return EXIT_FAILURE;

    size_t numSegments;
    segment *segments = computeSegments(&mat, &numSegments);

    makeComponents(segments, numSegments);

    // TODO make the output name link to the passed-in location
    writeSegments("example.ccl", segments, numSegments, mat.length, &status);

    if (!status)
        return EXIT_FAILURE;

    free(mat.x);
    free(mat.y);
    free(mat.z);

    free(segments);

    return EXIT_SUCCESS;
}
