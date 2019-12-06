#include "component.h"


segment *findSet(segment *segments, segment *candidate)
{
    segment segment = *candidate;

    // As long as the currently considered segment is not its own parent, we
    // have yet to reach the root segment.
    while (segments[segment.parent].parent != segment.parent)
        segment = segments[segment.parent];

    return segments + segment.parent;
}
