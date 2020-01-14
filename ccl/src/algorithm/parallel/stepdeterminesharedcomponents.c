#include "algorithm/parallel.h"
#include "segment.h"

#include <assert.h>
#include <bsp.h>
#include <component.h>
#include <stdlib.h>


void stepDetermineSharedComponents()
{
    bsp_nprocs_t messages;
    bsp_size_t qSize;
    bsp_qsize(&messages, &qSize);

    size_t const numSegments = qSize / sizeof(segment);
    segment *segments = malloc(numSegments * sizeof(segment));

    size_t offset = 0;

    for (size_t idx = 0; idx != messages; ++idx)
    {
        bsp_size_t mSize;
        bsp_get_tag(&mSize, NULL);

        bsp_move(segments + offset, mSize);
        offset += mSize / sizeof(segment);
    }

    // Restore iteration order for the received segments and reset their set
    // associations.
    qsort(segments, numSegments, sizeof(segment), segCoordCmp);
    makeSets(segments, numSegments);

    // TODO: this can *maybe* be done using the sequential algorithm in some
    //  modified form. Think about it, if time permits.
    for (size_t outer = 0; outer != numSegments; ++outer)
    {
        segment first = segments[outer];

        for (size_t inner = outer + 1; inner != numSegments; ++inner)
        {
            segment second = segments[inner];

            // The second segment came from a processor that does not neighbour
            // the first segment's processor. The coordinates and labels can
            // never compare equal beyond this point, so we break.
            if (second.label / NUM_VOXELS > 1 + first.label / NUM_VOXELS)
                break;

            // The segments overlap (shared boundary), or the labels need to
            // agree (they are in the same component on the origin processor).
            if (isEqual(&first, &second) || first.label == second.label)
                merge(&first, &second);
        }
    }

    // Update our segments with the new labelling.
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        if (segments[idx].label / NUM_VOXELS != bsp_pid())
            continue;  // we do not own this segment.

        segment *curr = bsearch(segments + idx,
                                SEGMENTS,
                                NUM_SEGMENTS,
                                sizeof(segment),
                                segCoordCmp);
        assert(curr != NULL);

        findSet(curr)->label = findSet(segments + idx)->label;
    }

    labelSegments(SEGMENTS, NUM_SEGMENTS);

    free(segments);
}
