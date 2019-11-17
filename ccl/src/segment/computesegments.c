#include "segment.h"

#include <assert.h>
#include <stdlib.h>


segment_t *computeSegments(short const *vector,
                           size_t length,
                           size_t numSegments)
{
    assert(length > 1);  // since we need to compare at least two values.

    segment_t *segments = malloc(numSegments * sizeof(segment_t));

    size_t idxSegment = 0;  // segment counter
    size_t offset = 0;      // index counter

    // Iterate from the current offset until the next crossing. At a crossing,
    // we create a segment representing the contiguous blocks in the interval
    // [offset, idx]. TODO: this doesn't work properly *yet*.
    for (size_t idx = 0; idx != length; ++idx)
        if (vector[idx - 1] != vector[idx])
        {
            segments[idxSegment++] = (segment_t){offset, idx};
            offset = idx + 1;
        }

    // We must have exactly numSegments segments in the segments array.
    assert(idxSegment == numSegments);

    return segments;
}
