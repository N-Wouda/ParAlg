#include "component.h"


void merge(segment *segments, segment *first, segment *second)
{
    link(findSet(segments, first), findSet(segments, second));
}
