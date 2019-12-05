#include "main.h"

#include "segment.h"
#include "sparse.h"

#include <stdlib.h>
#include <stdio.h>


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

    size_t numSegments;
    segment_t *segments = computeSegments(&mat, &numSegments);

    for (size_t idx = 0; idx != numSegments; ++idx)
        printf("SEGMENT: x=%zu, y=%zu, z1=%zu, z2=%zu\n",
            segments[idx].x, segments[idx].y, segments[idx].z1,
            segments[idx].z2);

    free(mat.x);
    free(mat.y);
    free(mat.z);

    free(segments);

    return EXIT_SUCCESS;
}
