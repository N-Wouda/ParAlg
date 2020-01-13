#include "component.h"


void labelSegments(segment *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
        segments[idx].label = findSet(segments + idx)->label;
}
