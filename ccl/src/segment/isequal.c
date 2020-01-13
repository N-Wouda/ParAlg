#include "segment.h"

bool isEqual(segment const *candidate, segment const *target)
{
    // clang-format off
    return candidate->x == target->x
        && candidate->y == target->y
        && candidate->zFirst == target->zFirst
        && candidate->zLast == target->zLast;
    // clang-format on
}
