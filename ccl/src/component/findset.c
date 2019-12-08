#include "component.h"


segment *findSet(segment *candidate)
{
    segment segment = *candidate;

    // As long as the currently considered segment is not its own parent, we
    // have yet to reach the root segment.
    while ((segment.parent)->parent != segment.parent)
        segment = *segment.parent;

    return segment.parent;
}
