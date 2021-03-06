#include "algorithm/steps.h"

#include <bsp.h>


void stepReturnLabelledSegments()
{
    bsp_size_t offset = bsp_pid() != 0;

    // We should not send the overlapping parts to the first processor twice.
    // This ensures we only send it once.
    if (bsp_pid() != 0)
        while (offset != NUM_SEGMENTS
               && SEGMENTS[offset - 1].x == SEGMENTS[offset].x)
            offset++;

    bsp_send(0,
             NULL,
             SEGMENTS + offset,
             (NUM_SEGMENTS - offset) * sizeof(segment));
}
