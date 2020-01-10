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

    // Restore iteration order for the received segments and reset their set
    // associations.
    qsort(segments, numSegments, sizeof(segment), segCoordCmp);
    makeSets(segments, numSegments);

    // TODO make this use the sequential algorithm. (but how?)
    for (size_t outer = 0; outer != numSegments; ++outer)
        for (size_t inner = 0; inner != numSegments; ++inner)
        {
            if (inner == outer)
                continue;

            segment first = segments[outer];
            segment second = segments[inner];

            // The segments overlap (shared boundary), or the labels need to
            // agree (they are in the same component on the origin processor).
            if (isEqual(&first, &second) || first.label == second.label)
                merge(&first, &second);
        }

    labelSegments(segments, numSegments);

    // Update our segments with the new labelling.
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment *curr = bsearch(segments + idx,
                                SEGMENTS,
                                NUM_SEGMENTS,
                                sizeof(segment),
                                segCoordCmp);

        if (curr == NULL)  // We do not own this segment.
            continue;

        findSet(curr)->label = segments[idx].label;
    }

    labelSegments(SEGMENTS, NUM_SEGMENTS);

    free(segments);
}
