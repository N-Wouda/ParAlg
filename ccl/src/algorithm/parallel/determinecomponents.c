#include "algorithm.h"
#include "algorithm/parallel.h"
#include "component.h"
#include "sparse.h"

#include <assert.h>
#include <bsp.h>
#include <stdlib.h>
#include <string.h>

_Thread_local segment *SEGMENTS;
_Thread_local size_t NUM_SEGMENTS;


void determineComponents()
{
    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    if (messages != 3)  // should equal the number of dimensions: x, y, z.
        bsp_abort("%u: expected 3 messages, got %u.\n", bsp_pid(), messages);

    // Number of bytes per dimension: x, y, z.
    size_t numBytes = qSize / messages;

    // The following is a bit abstract, but constructs a matrix from the
    // received dimension arrays. These are received in order of x, y, z.
    matrix mat = {NULL, NULL, NULL, numBytes / sizeof(size_t)};
    size_t **dimensions[3] = {&mat.x, &mat.y, &mat.z};

    for (size_t idx = 0; idx != 3; ++idx)
    {
        // Allocates some memory for the dimension, and then populates it from
        // the received message.
        *dimensions[idx] = malloc(numBytes);
        assert(*dimensions[idx] != NULL);

        size_t mSize;
        bsp_get_tag(&mSize, NULL);

        assert(mSize == numBytes);
        bsp_move(*dimensions[idx], mSize);
    }

    // Use the sequential algorithm to label the received matrix.
    SEGMENTS = sequential(&mat, &NUM_SEGMENTS);

    free(mat.x);
    free(mat.y);
    free(mat.z);

    // TODO - break it up here, and rethink/-write everything below. Do check!

    // 1. Memcpy shared first and last boundary, if applicable.
    // 2. CCL those and compare to segments above.
    // 3. Send those segments to other processors, with labelling as in the
    //    initial list.

    if (bsp_pid() != 0)
    {
        size_t idx = 1;

        while (SEGMENTS[idx - 1].x == SEGMENTS[idx].x && idx < NUM_SEGMENTS)
            idx++;

        // Copy the slice, so we can relabel these segments without interfering
        // with the actual slices.
        size_t const sliceSegments = idx;
        size_t const from = 0;

        segment *copy = malloc(sliceSegments * sizeof(segment));
        assert(copy != NULL);

        memcpy(copy, SEGMENTS + from, sliceSegments * sizeof(segment));

        // Reset each segment to point to itself.
        for (size_t idx = 0; idx != sliceSegments; ++idx)
            copy[idx].parent = copy + idx;

        makeComponents(copy, sliceSegments);

        for (size_t idx = 0; idx != sliceSegments; ++idx)
        {
            segment seg = SEGMENTS[idx + from];
            segment cpy = copy[idx];

            segment *cpyRoot = findSet(cpy.parent);
            segment *segRoot = findSet(seg.parent);

            if (cpyRoot != segRoot)
            {
                cpyRoot->parent = segRoot;
                cpy.label = seg.label;

                for (size_t proc = 0; proc != bsp_nprocs(); ++proc)
                    bsp_send(proc, NULL, &cpy, sizeof(segment));
            }
        }

        free(copy);
    }

    if (bsp_pid() != bsp_nprocs() - 1)
    {
        size_t idx = NUM_SEGMENTS - 1;

        while (SEGMENTS[idx - 1].x == SEGMENTS[idx].x && idx > 0)
            idx--;

        // Copy the slice, so we can relabel these segments without interfering
        // with the actual slices.
        size_t const sliceSegments = NUM_SEGMENTS - idx;
        size_t const from = idx;

        segment *copy = malloc(sliceSegments * sizeof(segment));
        assert(copy != NULL);

        memcpy(copy, SEGMENTS + idx, sliceSegments * sizeof(segment));

        // Reset each segment to point to itself.
        for (size_t idx = 0; idx != sliceSegments; ++idx)
            copy[idx].parent = copy + idx;

        makeComponents(copy, sliceSegments);

        for (size_t idx = 0; idx != sliceSegments; ++idx)
        {
            segment seg = SEGMENTS[idx + from];
            segment cpy = copy[idx];

            segment *cpyRoot = findSet(cpy.parent);
            segment *segRoot = findSet(seg.parent);

            if (cpyRoot != segRoot)
            {
                cpyRoot->parent = segRoot;
                cpy.label = seg.label;

                for (size_t proc = 0; proc != bsp_nprocs(); ++proc)
                    bsp_send(proc, NULL, &cpy, sizeof(segment));
            }
        }

        free(copy);
    }
}
