#include "component.h"


void makeSets(segment *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
        segments[idx].parent = segments + idx;

    // TODO update rank as well?
}
