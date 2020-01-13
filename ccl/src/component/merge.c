#include "component.h"


void merge(segment *first, segment *second)
{
    segment *firstRoot = findSet(first);
    segment *secondRoot = findSet(second);

    if (firstRoot->rank > secondRoot->rank)
        secondRoot->parent = firstRoot;
    else
    {
        firstRoot->parent = secondRoot;

        if (firstRoot->rank == secondRoot->rank)
            secondRoot->rank++;
    }
}
