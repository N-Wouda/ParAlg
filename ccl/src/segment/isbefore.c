#include "component.h"

#include <assert.h>


bool isBefore(segment const *candidate, segment const *target)
{
    assert(candidate->zLast > 0);

    // clang-format off
    return candidate->x < target->x
        || (candidate->x == target->x && candidate->y < target->y)
        || (candidate->x == target->x && candidate->y == target->y
            && candidate->zLast - 1 < target->zFirst);  // last is exclusive.
    // clang-format on
}
