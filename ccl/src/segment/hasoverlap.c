#include "segment.h"


bool hasOverlap(segment const *candidate, segment const *target)
{
    // clang-format off
    return candidate->x == target->x
        && candidate->y == target->y
        && candidate->zFirst < target->zLast
        && candidate->zLast > target->zFirst;
    // clang-format on
}
