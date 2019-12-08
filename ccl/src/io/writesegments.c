#include "io.h"

#include <stdio.h>


void writeSegments(char const *location,
                   segment *segments,
                   size_t numSegments,
                   size_t numElements,
                   bool *status)
{
    *status = false;

    FILE *file = fopen(location, "w");

    if (file == NULL)
        return;

    fprintf(file, "%zu\n", numElements);

    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment const segment = segments[idx];
        size_t const label = segment.parent - segments;

        for (size_t z = segment.zFirst; z != segment.zLast; ++z)
            fprintf(file, "%zu %zu %zu %zu\n", segment.x, segment.y, z, label);
    }

    fclose(file);
    *status = true;
}
