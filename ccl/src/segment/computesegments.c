#include "segment.h"
#include "sparse.h"

#include <assert.h>
#include <stdlib.h>


segment_t *computeSegments(matrix_t const *mat, size_t *numSegments)
{
    *numSegments = countSegments(mat);

    segment_t *segments = malloc((*numSegments) * sizeof(segment_t));
    size_t segIdx = 0;

    // The very first segment is a bit unique, as it cannot be determined by
    // element-wise comparison like the others. As such, we initialise it here.
    segments[segIdx] = (segment_t){mat->x[0],
                                   mat->y[0],
                                   mat->z[0],
                                   mat->z[0],
                                   &segments[segIdx]};

    for (size_t matIdx = 1; matIdx != mat->length; ++matIdx)
        if (isNewSegment(mat, matIdx))
        {
            segments[++segIdx] = (segment_t){mat->x[matIdx],
                                             mat->y[matIdx],
                                             mat->z[matIdx],
                                             mat->z[matIdx]};

            // Initially each segment is its own component and thus points to
            // itself.
            segments[segIdx].parent = &segments[segIdx];
        }
        else
            segments[segIdx].zLast++;

    assert(segIdx + 1 == *numSegments);

    return segments;
}
