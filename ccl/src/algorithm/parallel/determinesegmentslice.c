#include "algorithm/parallel.h"

#include <assert.h>


void determineSegmentSlice(segment const *segments,
                           size_t numSegments,
                           size_t proc,
                           size_t numProcs,
                           size_t *low,
                           size_t *high)
{
    assert(numSegments > 0);
    assert(proc < numProcs);

    size_t const numItems = numSegments / numProcs;

    // This is a nominal slice, but will be adjusted below to account for
    // any breaks in x-values.
    *low = proc * numItems;
    *high = (proc + 1) * numItems + (proc != numProcs - 1);

    if (proc != 0)
        // If this is not the first processor, we have a boundary with the
        // preceding processor and should determine an overlapping slice.
        while (*low != 0 && segments[*low - 1].x == segments[*low].x)
            (*low)--;

    if (proc != numProcs - 1)
        // A similar argument holds when this is not the last processor, but
        // now the overlap is with the succeeding processor.
        while (*high != numSegments
               && segments[*high - 1].x == segments[*high].x)
            (*high)++;
    else
        // numItems rounds down, so this ensures the final few segments all
        // go to the last processor.
        *high = numSegments;

    assert(*high <= numSegments);
}
