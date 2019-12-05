#include "component.h"

#include <stdio.h>
#include <stdlib.h>

int cmp(void const *a, void const *b);


void makeComponents(segment_t *segments, size_t numSegments)
{
    // TODO: all this is really crap
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment_t const segment = segments[idx];
        segment_t previous[2] = {{segment.x - 1, segment.y},
                                 {segment.x, segment.y - 1}};

        for (size_t prevIdx = 0; prevIdx != 2; ++prevIdx)
        {
            void *res = bsearch(previous + prevIdx,
                                segments,
                                numSegments,
                                sizeof(segment_t),
                                cmp);

            if (res != NULL)
            {
                printf("idx = %zu\n", idx);
            }
        }
    }
}

int cmp(void const *a, void const *b)
{
    segment_t const key = *(segment_t *) a;
    segment_t const elem = *(segment_t *) b;

    if ((key.x < elem.x && key.y == elem.y)
        || (key.x == elem.x && key.y < elem.y))
        return -1;

    if (key.x == elem.x && key.y == elem.y)
        return 0;

    return 1;
}
