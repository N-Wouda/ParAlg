#include "segment.h"
#include "sparse.h"

#include <assert.h>
#include <stdlib.h>


segment *computeSegments(matrix const *mat, size_t *numSegments)
{
    assert(mat->length > 0);

    *numSegments = countSegments(mat);
    segment *segments = malloc((*numSegments) * sizeof(segment));

    size_t segIdx = 0;

    // The very first segment is a bit unique, as it cannot be determined by
    // element-wise comparison like the others.
    segments[segIdx] = makeSegment(mat, 0);

    for (size_t matIdx = 1; matIdx != mat->length; ++matIdx)
        if (isNewSegment(mat, matIdx))
            segments[++segIdx] = makeSegment(mat, matIdx);
        else
            segments[segIdx].zLast++;

    assert(segIdx + 1 == *numSegments);

    return segments;
}
