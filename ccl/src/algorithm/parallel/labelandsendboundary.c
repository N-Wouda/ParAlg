#include "algorithm/parallel.h"
#include "component.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>
#include <string.h>


void labelAndSendBoundary(size_t numSegments, size_t from)
{
    segment *copies = malloc(numSegments * sizeof(segment));
    assert(copies != NULL);

    memcpy(copies, SEGMENTS + from, numSegments * sizeof(segment));

    // Reset each copied segment to point to itself, and relabel the copies.
    for (size_t idx = 0; idx != numSegments; ++idx)
        copies[idx].parent = copies + idx;

    makeComponents(copies, numSegments);

    // We have a boundary-disjoint component only when the copies's root segment
    // is different from the original root segment. These we communicate to all
    // processors.
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = SEGMENTS[from + idx];
        segment copy = copies[idx];

        segment *copyRoot = findSet(&copy);
        segment *segRoot = findSet(&seg);

        if (copyRoot != segRoot)
        {
            copyRoot->parent = segRoot;
            copy.label = seg.label;

            for (size_t proc = 0; proc != bsp_nprocs(); ++proc)
                bsp_send(proc, NULL, &copy, sizeof(segment));
        }
    }

    free(copies);
}
