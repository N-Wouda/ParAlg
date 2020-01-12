#include "algorithm.h"
#include "algorithm/parallel.h"
#include "component.h"
#include "sparse.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>


void stepDetermineComponents()
{
    bsp_nprocs_t messages;
    bsp_size_t qSize;
    bsp_qsize(&messages, &qSize);

    if (messages != 2)  // segments and the label space.
        bsp_abort("%u: expected 2 messages, got %u.\n", bsp_pid(), messages);

    NUM_SEGMENTS = (qSize - sizeof(size_t)) / sizeof(segment);

    for (size_t idx = 0; idx != messages; ++idx)
    {
        bsp_size_t mSize;
        bsp_size_t tag;
        bsp_get_tag(&mSize, &tag);

        assert(tag == 0 || tag == 1);

        if (tag == 0)   // segments
        {
            assert(mSize == qSize - sizeof(size_t));
            assert(mSize == NUM_SEGMENTS * sizeof(segment));

            SEGMENTS = malloc(mSize);
            assert(SEGMENTS != NULL);

            bsp_move(SEGMENTS, mSize);
        }
        else if (tag == 1) // label space
        {
            assert(mSize == sizeof(size_t));
            bsp_move(&NUM_VOXELS, mSize);
        }
        else
            bsp_abort("%u: tag %d not understood\n", bsp_pid(), tag);
    }

    makeSets(SEGMENTS, NUM_SEGMENTS);
    makeComponents(SEGMENTS, NUM_SEGMENTS);
    labelSegments(SEGMENTS, NUM_SEGMENTS);

    // Guarantees we assign globally unique labels to each component.
    for (size_t idx = 0; idx != NUM_SEGMENTS; ++idx)
        SEGMENTS[idx].label += bsp_pid() * NUM_VOXELS;

    // Determines the boundaries for the processor, and labels/sends the
    // appropriate boundary components to the other processors.
    if (bsp_pid() != 0)
    {
        size_t numSegments = 1;

        // Find the last index of the first x-value we have.
        while (SEGMENTS[numSegments - 1].x == SEGMENTS[numSegments].x
               && numSegments < NUM_SEGMENTS)
            numSegments++;

        labelAndSendBoundary(numSegments, 0);
    }

    if (bsp_pid() != bsp_nprocs() - 1)
    {
        size_t from = NUM_SEGMENTS - 1;

        // Finds the first index of the last x-value we have.
        while (SEGMENTS[from - 1].x == SEGMENTS[from].x && from > 0)
            from--;

        labelAndSendBoundary(NUM_SEGMENTS - from, from);
    }
}
