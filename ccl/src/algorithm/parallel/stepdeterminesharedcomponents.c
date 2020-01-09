#include "algorithm/parallel.h"
#include "segment.h"

#include <assert.h>
#include <bsp.h>
#include <component.h>
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

    // Restore iteration order for the received segments.
    qsort(segments, numSegments, sizeof(segment), segCmp);

    // Since these pointers reference objects on the other processors, we
    // should initially reset each segment to its own set.
    for (size_t idx = 0; idx != numSegments; ++idx)
        segments[idx].parent = segments + idx;

    // TODO make this use the sequential algorithm.
    for (size_t i = 0; i != numSegments; ++i)
        for (size_t j = 0; j != numSegments; ++j)
        {
            if (i == j)
                continue;

            segment *first = segments + i;
            segment *second = segments + j;

            // The segments overlap (shared boundary), or the labels need to
            // agree (they are in the same component on the origin processor).
            if (isEqual(first, second) || first->label == second->label)
                merge(first, second);
        }

    labelSegments(segments, numSegments);

    // TODO make this more efficient
    for (size_t i = 0; i != numSegments; ++i)
        for (size_t j = 0; j != NUM_SEGMENTS; ++j)
        {
            segment const seg = segments[i];
            segment curr = SEGMENTS[j];

            if (isEqual(&seg, &curr))
                findSet(&curr)->label = seg.label;
        }

    labelSegments(SEGMENTS, NUM_SEGMENTS);

    free(segments);
}
