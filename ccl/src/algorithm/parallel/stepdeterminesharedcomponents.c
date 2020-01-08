#include "segment.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>


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

    // TODO label received boundary segments.

    // 1. Sort the segments so they admit the iteration order.
    // 2. Re-use sequential algorithm to label them, but this will require a
    //    bit of customization (if they already have the same labels, they're
    //    neighbours too!).
    // 3. Write final labelling to file?

    free(segments);
}
