#include "component.h"


segment *sequential(matrix const *mat, size_t *numSegments)
{
    segment *segments = computeSegments(mat, numSegments);

    makeSets(segments, *numSegments);
    makeComponents(segments, *numSegments);
    labelSegments(segments, *numSegments);

    return segments;
}
