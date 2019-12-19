#include "component.h"


segment *sequential(matrix const *mat, size_t *numSegments)
{
    segment *segments = computeSegments(mat, numSegments);
    makeComponents(segments, *numSegments);

    return segments;
}
