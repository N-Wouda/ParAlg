#include "component.h"


void merge(segment_t *segments, segment_t *first, segment_t *second)
{
    link(findSet(segments, first), findSet(segments, second));
}
