#include "component.h"

bool isRoot(segment const *candidate)
{
    return candidate->parent == candidate;
}
