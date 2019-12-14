#include "component.h"

#include <assert.h>
#include <stdio.h>


void writeSegments(char const *location,
                   segment const *segments,
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
        segment const seg = segments[idx];
        segment const *root = findSet(seg.parent);

        assert(isRoot(root));

        size_t const label = root - segments;

        for (size_t z = seg.zFirst; z != seg.zLast; ++z)
            fprintf(file, "%zu %zu %zu %zu\n", seg.x, seg.y, z, label);
    }

    fclose(file);
    *status = true;
}
