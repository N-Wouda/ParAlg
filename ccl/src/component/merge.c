#include "component.h"


void merge(segment *first, segment *second)
{
    link(findSet(first), findSet(second));
}
