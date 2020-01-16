#include "algorithm/parallel.h"

#include <bsp.h>
#include <stdlib.h>


segment *receiveSegments(size_t *numSegments)
{
    bsp_nprocs_t messages;
    bsp_size_t qSize;
    bsp_qsize(&messages, &qSize);

    *numSegments = qSize / sizeof(segment);
    segment *segments = malloc(*numSegments * sizeof(segment));

    size_t offset = 0;

    for (size_t idx = 0; idx != messages; ++idx)
    {
        bsp_size_t mSize;
        bsp_get_tag(&mSize, NULL);

        bsp_move(segments + offset, mSize);
        offset += mSize / sizeof(segment);
    }

    return segments;
}
