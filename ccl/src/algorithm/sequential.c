#include "component.h"


segment *sequential(matrix const *mat, size_t *numSegments)
{
    segment *segments = computeSegments(mat, numSegments);
    makeComponents(segments, *numSegments);

    for (size_t idx = 0; idx != *numSegments; ++idx)
        segments[idx].label = findSet(segments + idx)->label;

    return segments;
}
