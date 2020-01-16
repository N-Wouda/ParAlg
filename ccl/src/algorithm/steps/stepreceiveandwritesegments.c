#include "algorithm/parallel.h"
#include "algorithm/steps.h"
#include "io.h"

#include <bsp.h>
#include <stdlib.h>


void stepReceiveAndWriteSegments()
{
    if (bsp_pid() != 0)
        return;

    size_t numSegments;
    segment *segments = receiveSegments(&numSegments);

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
