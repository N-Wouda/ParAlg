#include "component.h"


segment *findSet(segment *candidate)
{
    // One-pass path halving method. This ensures all nodes in the set point
    // to the root node - eventually.
    while (!isRoot(candidate))
    {
        candidate->parent = candidate->parent->parent;
        candidate = candidate->parent;
    }

    return candidate;
}
