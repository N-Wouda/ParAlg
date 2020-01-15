#include "algorithm/parallel.h"
#include "component.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


segment *labelBoundary(segment const *segments,
                       size_t numSegments,
                       size_t from,
                       size_t *numRoots)
{
    segment *copies = malloc(numSegments * sizeof(segment));
    assert(copies != NULL);

    memcpy(copies, segments + from, numSegments * sizeof(segment));

    // Reset each copied segment to point to itself, and relabel the copies.
    makeSets(copies, numSegments);
    makeComponents(copies, numSegments);

    // There are at most as many roots as there are boundary segments.
    segment *roots = malloc(numSegments * sizeof(segment));
    assert(roots != NULL);

    size_t rootIdx = 0;

    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = segments[from + idx];
        segment *copyRoot = findSet(copies + idx);
        segment *segRoot = findSet(&seg);

        // If we have a copyRoot that's not the same as the segRoot, it must be
        // a (new) boundary-disjoint component. This implies seg is in a
        // boundary-disjoint set. Updating the copyRoot to point to the segRoot
        // ensures we do not find any other segments in this boundary-disjoint
        // component.
        if (copyRoot != segRoot)
        {
            copyRoot->parent = segRoot;
            roots[rootIdx++] = seg;
        }
    }

    free(copies);

    *numRoots = rootIdx;
    return roots;
}
