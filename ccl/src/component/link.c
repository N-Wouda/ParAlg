#include "component.h"


void link(segment_t *first, segment_t *second)
{
    if (first->rank > second->rank)
        second->parent = first->parent;
    else
    {
        first->parent = second->parent;

        if (first->rank == second->rank)
            second->rank++;
    }
}
