#include "segment.h"
#include "sparse.h"

#include <assert.h>
#include <stdlib.h>


segment_t *computeSegments(matrix_t const *mat, size_t *numSegments)
{
    assert(mat->length > 1);

    *numSegments = countSegments(mat);

    segment_t *segments = malloc((*numSegments) * sizeof(segment_t));
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
        }
        else
            segments[segIdx].zLast++;

    assert(segIdx + 1 == *numSegments);

    return segments;
}
