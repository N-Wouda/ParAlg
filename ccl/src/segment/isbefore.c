#include "component.h"


bool isBefore(segment const *candidate, segment const *target)
{
    // clang-format off
    return candidate->x < target->x
        || (candidate->x == target->x && candidate->y < target->y)
        || (candidate->x == target->x && candidate->y == target->y
            && candidate->zLast - 1 < target->zFirst);  // last is exclusive.
    // clang-format on
}
