#include "io.h"

#include <stdio.h>


void writeSegments(char const *location,
                   segment_t *segments,
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
        segment_t const segment = segments[idx];

        for (size_t z = segment.zFirst; z != segment.zLast + 1; ++z)
        {
            fprintf(file,
                    "%zu %zu %zu %zu\n",
                    segment.x,
                    segment.y,
                    z,
                    segment.parent);
        }
    }

    fclose(file);
    *status = true;
}
