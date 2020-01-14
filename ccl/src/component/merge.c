#include "component.h"

#include <assert.h>


void merge(segment *first, segment *second)
{
    segment *firstRoot = findSet(first);
    segment *secondRoot = findSet(second);

    if (firstRoot == secondRoot)  // no-op
        return;

    if (firstRoot->rank > secondRoot->rank)
        secondRoot->parent = firstRoot;
    else
    {
        firstRoot->parent = secondRoot;

        if (firstRoot->rank == secondRoot->rank)
            secondRoot->rank++;
    }

    assert(findSet(first) == findSet(second));  // post-condition
}
