#include "algorithm/parallel.h"
#include "segment.h"

#include <bsp.h>
#include <io.h>
#include <stdlib.h>


void stepReceiveAndWriteSegments()
{
    if (bsp_pid() != 0)
        return;

    bsp_nprocs_t messages;
    bsp_size_t qSize;
    bsp_qsize(&messages, &qSize);

    size_t const numSegments = qSize / sizeof(segment);
    segment *segments = malloc(qSize);

    size_t offset = 0;

    for (size_t message = 0; message != messages; ++message)
    {
        bsp_size_t mSize;
        bsp_size_t tag;
        bsp_get_tag(&mSize, &tag);

        // After receiving mSize bytes, we must update the offset to just
        // beyond these, such that the next message may be received properly.
        bsp_move(segments + offset, mSize);
        offset += mSize / sizeof(segment);
    }

    // Restore iteration order.
    qsort(segments, numSegments, sizeof(segment), segCoordCmp);

    bool status = true;
    writeSegments(ARGUMENTS.outLocation,
                  segments,
                  numSegments,
                  NUM_VOXELS,
                  &status);

    free(segments);

    if (!status)
        bsp_abort("Failed to write segments to file.\n");
}
