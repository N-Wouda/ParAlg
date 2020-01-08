#include "segment.h"

#include <assert.h>
#include <bsp.h>
#include <component.h>
#include <stdio.h>
#include <stdlib.h>

static int segCmp(void const *a, void const *b);

void stepDetermineSharedComponents()
{
    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    size_t const numSegments = qSize / sizeof(segment);
    assert(numSegments == messages);

    segment *segments = malloc(numSegments * sizeof(segment));

    for (size_t idx = 0; idx != messages; ++idx)
    {
        size_t mSize;
        bsp_get_tag(&mSize, NULL);
        assert(mSize == sizeof(segment));

        bsp_move(segments + idx, mSize);
    }

    // Since these pointers reference objects on the other processors, we
    // should initially reset each segment to its own set.
    for (size_t idx = 0; idx != numSegments; ++idx)
        segments[idx].parent = segments + idx;

    // TODO label received boundary segments.
    qsort(segments, numSegments, sizeof(segment), segCmp);

    for (size_t idx = 0; idx != numSegments; ++idx)
        printf("%u: %zu - [%zu, %zu, %zu, %zu]\n",
               bsp_pid(),
               idx,
               segments[idx].x,
               segments[idx].y,
               segments[idx].zFirst,
               segments[idx].zLast);

    // 1. Sort the segments so they admit the iteration order.
    // 2. Re-use sequential algorithm to label them, but this will require a
    //    bit of customization (if they already have the same labels, they're
    //    neighbours too!).
    // 3. Write final labelling to file?

    free(segments);
}

static int segCmp(void const *a, void const *b)
{
    segment *segA = (segment *) a;
    segment *segB = (segment *) b;

    if (isBefore(segA, segB))
        return -1;

    if (isEqual(segA, segB))
        return 0;

    return 1;
}
