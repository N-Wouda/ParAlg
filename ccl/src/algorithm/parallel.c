#include "algorithm/parallel.h"

#include "io.h"

#include <bsp.h>

_Thread_local segment *SEGMENTS;
_Thread_local size_t NUM_SEGMENTS;

void parallel()
{
    bsp_begin(ARGUMENTS.numProcs);

    stepSendMatrices();  // Shares sub-matrices with other processors.
    bsp_sync();

    stepDetermineComponents();  // Label own matrix and shared boundaries.
    bsp_sync();                 // Communicate shared boundary components.

    stepDetermineSharedComponents();  // Determine component structure for shared components.
    bsp_sync();

    // TODO receive all segments at first processor and write to file?

    bsp_end();
}
