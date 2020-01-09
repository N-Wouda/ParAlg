#include "algorithm/parallel.h"

#include <bsp.h>


void returnLabelledSegments()
{
    // We should not send the overlapping parts to the first processor twice.
    // This ensures we only send it once.
    size_t offset = 0;

    if (bsp_pid() != 0)
    {
        while (SEGMENTS[offset].x == SEGMENTS[offset + 1].x
               && offset < NUM_SEGMENTS)
            offset++;
    }

    bsp_send(0,
             NULL,
             SEGMENTS + offset,
             (NUM_SEGMENTS - offset) * sizeof(segment));
}
