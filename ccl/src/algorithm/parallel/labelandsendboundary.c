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
    makeSets(copies, numSegments);
    makeComponents(copies, numSegments);

    bsp_size_t currProc = bsp_pid();

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

            for (bsp_pid_t proc = 0; proc != bsp_nprocs(); ++proc)
                bsp_send(proc, &currProc, &seg, sizeof(segment));
        }
    }

    free(copies);
}
