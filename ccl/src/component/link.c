#include "component.h"


void link(segment *first, segment *second)
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
