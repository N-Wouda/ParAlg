#include "segment.h"
#include "sparse.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b);

long offset(size_t key, segment *segments, size_t numSegments);

segment *computeSegments(matrix const *mat, size_t *numSegments)
{
    assert(mat->length > 1);

    *numSegments = countSegments(mat);

    segment *segments = malloc((*numSegments) * sizeof(segment));
    size_t segIdx = 0;

    // The very first segment is a bit unique, as it cannot be determined by
    // element-wise comparison like the others. Initially, each segment points
    // to itself (same below for other segments).
    segments[segIdx] = makeSegment(mat, 0, segIdx);

    for (size_t matIdx = 1; matIdx != mat->length; ++matIdx)
        if (isNewSegment(mat, matIdx))
        {
            segIdx++;
            segments[segIdx] = makeSegment(mat, matIdx, segIdx);

            // Computes offsets to the previous value of x in the segments
            // array (prevX), and the current value (currX). This is used to
            // efficiently compute components later. If the current x index is
            // zero, there is no previous value and we use the dummy by default.

            // clang-format off
            segments[segIdx].prevX = mat->x[matIdx] > 0
                ? offset(mat->x[matIdx] - 1, segments, segIdx + 1)
                : -1;
            // clang-format on

            // TODO check current -1 for first segment, start from prevX idx?
            segments[segIdx].currX = offset(mat->x[matIdx],
                                            segments,
                                            segIdx + 1);
        }
        else
            segments[segIdx].zLast++;

    assert(segIdx + 1 == *numSegments);

    return segments;
}

int compare(void const *a, void const *b)
{
    size_t key = *((size_t *) a);
    segment elem = *((segment *) b);

    if (key == elem.x)
        return 0;
    else if (key < elem.x)
        return -1;
    else
        return 1;
}

// TODO this is now a binary search, but I think we construct these offsets
// in passing with the segments.
long offset(size_t key, segment *segments, size_t numSegments)
{
    void *res = bsearch(&key, segments, numSegments, sizeof(segment), compare);

    if (res == NULL)
        return -1;

    segment *seg = (segment *) res;

    // TODO this should be done by binary search, and not be needed after.
    // Perhaps roll our own bsearch?
    while (seg->x == key && seg >= segments)
        seg--;

    return seg - segments + 1;
}
