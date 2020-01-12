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

    segment *roots = malloc(numSegments * sizeof(segment));
    assert(roots != NULL);

    size_t rootIdx = 0;

    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = SEGMENTS[from + idx];
        segment copy = copies[idx];

        segment *copyRoot = findSet(&copy);
        segment *segRoot = findSet(&seg);

        if (copyRoot != segRoot)
        {
            copyRoot->parent = segRoot;

            roots[rootIdx] = seg;
            rootIdx++;
        }
    }

    for (bsp_pid_t proc = 0; proc != bsp_nprocs(); ++proc)
        bsp_send(proc, &currProc, roots, (rootIdx + 1) * sizeof(segment));

    free(roots);
    free(copies);
}
