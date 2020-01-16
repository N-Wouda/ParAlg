#include "algorithm/parallel.h"
#include "algorithm/steps.h"
#include "component.h"
#include "sparse.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>


static void processBoundary(size_t numSegments, size_t from);  // helper method

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
        bsp_get_tag(&mSize, NULL);

        if (mSize == sizeof(size_t))  // label space
            bsp_move(&NUM_VOXELS, mSize);
        else  // segments
        {
            assert(mSize == qSize - sizeof(size_t));
            assert(mSize == NUM_SEGMENTS * sizeof(segment));

            SEGMENTS = malloc(mSize);
            assert(SEGMENTS != NULL);

            bsp_move(SEGMENTS, mSize);
        }
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
        while (numSegments != NUM_SEGMENTS
               && SEGMENTS[numSegments - 1].x == SEGMENTS[numSegments].x)
            numSegments++;

        processBoundary(numSegments, 0);
    }

    if (bsp_pid() != bsp_nprocs() - 1)
    {
        size_t from = NUM_SEGMENTS - 1;

        // Finds the first index of the last x-value we have.
        while (from != 0 && SEGMENTS[from - 1].x == SEGMENTS[from].x)
            from--;

        processBoundary(NUM_SEGMENTS - from, from);
    }
}

static void processBoundary(size_t numSegments, size_t from)
{
    size_t numRoots;
    segment *roots = labelBoundary(SEGMENTS, numSegments, from, &numRoots);

    for (bsp_pid_t proc = 0; proc != bsp_nprocs(); ++proc)
        bsp_send(proc, NULL, roots, numRoots * sizeof(segment));

    free(roots);
}
