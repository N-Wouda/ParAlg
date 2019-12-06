#include "component.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);

long offs(size_t key, segment *segments, size_t numSegments);

void makeComponents(segment *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = segments[idx];

        assert(seg.currX != -1);  // this would be very weird indeed.

        if (seg.prevX != -1)
        {
            long yMatch = offs(seg.y,
                               segments + seg.prevX,
                               seg.currX - seg.prevX + 1);

            if (yMatch != -1)
                printf("(x - 1, y) idx: %ld\n", seg.prevX + yMatch);
        }

        long yMatch = offs(seg.y - 1, segments + seg.currX, idx - seg.currX + 1);

        if (yMatch != -1)
            printf("(x, y - 1) idx: %ld\n", seg.currX + yMatch);
    }
}

int cmp(void const *a, void const *b)
{
    size_t key = *((size_t *) a);
    segment elem = *((segment *) b);

    if (key == elem.x)
        return 0;
    else if (key < elem.x)
        return -1;
    else
        return 1;
}

long offs(size_t key, segment *segments, size_t numSegments)
{
    void *res = bsearch(&key, segments, numSegments, sizeof(segment), cmp);
    return res == NULL ? -1 : (segment *) res - segments;
}
