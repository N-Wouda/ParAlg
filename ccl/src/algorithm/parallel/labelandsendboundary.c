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

    // There are at most as many roots as there are boundary segments.
    segment *roots = malloc(numSegments * sizeof(segment));
    assert(roots != NULL);

    size_t rootIdx = 0;

    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = SEGMENTS[from + idx];
        segment *copyRoot = findSet(copies + idx);
        segment *segRoot = findSet(&seg);

        if (copyRoot != segRoot)
        {
            copyRoot->parent = segRoot;
            roots[rootIdx++] = seg;
        }
    }

    for (bsp_pid_t proc = 0; proc != bsp_nprocs(); ++proc)
        // rootIdx doubles as the actual number of root segments.
        bsp_send(proc, &currProc, roots, rootIdx * sizeof(segment));

    free(roots);
    free(copies);
}
