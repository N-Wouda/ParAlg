#include "component.h"


segment_t *findSet(segment_t *segments, segment_t *candidate)
{
    segment_t segment = *candidate;

    // As long as the currently considered segment is not its own parent, we
    // have yet to reach the root segment.
    while (segments[segment.parent].parent != segment.parent)
        segment = segments[segment.parent];

    return segments + segment.parent;
}
