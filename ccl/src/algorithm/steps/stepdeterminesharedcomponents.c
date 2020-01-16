#include "algorithm/parallel.h"
#include "algorithm/steps.h"
#include "component.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>


void stepDetermineSharedComponents()
{
    size_t numSegments;
    segment *segments = receiveSegments(&numSegments);

    // Restore iteration order for the received segments and reset their set
    // associations.
    qsort(segments, numSegments, sizeof(segment), segTotalCmp);
    makeSets(segments, numSegments);

    // TODO: can be done using the sequential algorithm in some modified form?
    for (size_t outer = 0; outer != numSegments; ++outer)
    {
        segment first = segments[outer];

        for (size_t inner = outer + 1; inner != numSegments; ++inner)
        {
            segment second = segments[inner];

            // The second segment came from a processor that does not neighbour
            // the first segment's processor. The coordinates and labels can
            // never compare equal beyond this point, so we break.
            if (getOwningProcessor(&second, NUM_VOXELS)
                > getOwningProcessor(&first, NUM_VOXELS) + 1)
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
        if (getOwningProcessor(segments + idx, NUM_VOXELS) != bsp_pid())
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
