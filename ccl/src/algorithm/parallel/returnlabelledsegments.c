#include "algorithm/parallel.h"

#include <bsp.h>


void returnLabelledSegments()
{
    bsp_size_t offset = bsp_pid() != 0;
    bsp_size_t currProc = bsp_pid();

    // We should not send the overlapping parts to the first processor twice.
    // This ensures we only send it once.
    if (bsp_pid() != 0)
        while (SEGMENTS[offset - 1].x == SEGMENTS[offset].x
               && offset < NUM_SEGMENTS)
            offset++;

    bsp_send(0,
             &currProc,
             SEGMENTS + offset,
             (NUM_SEGMENTS - offset) * sizeof(segment));
}
