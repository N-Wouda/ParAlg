#include "main.h"

#include "component.h"
#include "segment.h"
#include "sparse.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    char *location;
    size_t numProcs;

    if (!arguments(argc, argv, &location, &numProcs))
        return EXIT_FAILURE;

    bool status = true;
    matrix_t const mat = readMatrix(location, &status);

    if (!status)
        return EXIT_FAILURE;

    size_t numSegments;
    segment_t *segments = computeSegments(&mat, &numSegments);

    for (size_t idx = 0; idx != numSegments; ++idx)
        printf("SEGMENT: x=%zu, y=%zu, zFirst=%zu, zLast=%zu,"
               " self=%zu, parent=%zu\n",
               segments[idx].x,
               segments[idx].y,
               segments[idx].zFirst,
               segments[idx].zLast,
               idx,
               segments[idx].parent);

    makeComponents(segments, numSegments);

    printf("--Components--\n");

    for (size_t idx = 0; idx != numSegments; ++idx)
        printf("SEGMENT: x=%zu, y=%zu, zFirst=%zu, zLast=%zu,"
               " self=%zu, parent=%zu\n",
               segments[idx].x,
               segments[idx].y,
               segments[idx].zFirst,
               segments[idx].zLast,
               idx,
               segments[idx].parent);

    free(mat.x);
    free(mat.y);
    free(mat.z);

    free(segments);

    return EXIT_SUCCESS;
}
