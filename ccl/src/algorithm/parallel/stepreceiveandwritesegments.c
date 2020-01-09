#include "algorithm/parallel.h"
#include "segment.h"

#include <assert.h>
#include <bsp.h>
#include <io.h>
#include <stdlib.h>


void stepReceiveAndWriteSegments()
{
    if (bsp_pid() != 0)
        return;

    unsigned int messages;
    size_t qSize;
    bsp_qsize(&messages, &qSize);

    assert(messages == bsp_nprocs());

    size_t const numSegments = qSize / sizeof(segment);
    segment *segments = malloc(numSegments * sizeof(segment));

    for (size_t idx = 0; idx != messages; ++idx)
    {
        size_t mSize;
        bsp_get_tag(&mSize, NULL);

        bsp_move(segments + idx, mSize);
    }

    bool status = true;

    writeSegments(ARGUMENTS.outLocation,
                  segments,
                  numSegments,
                  NUM_VOXELS,
                  &status);

    if (!status)
        bsp_abort("Failed to write segments to file.\n");

    free(segments);
}
