#include "algorithm/parallel.h"

#include "io.h"

#include <bsp.h>
#include <stdlib.h>

_Thread_local segment *SEGMENTS;
_Thread_local size_t NUM_SEGMENTS;
_Thread_local size_t NUM_VOXELS;

void parallel()
{
    bsp_begin(ARGUMENTS.numProcs);

    stepSendMatrices();  // Shares sub-matrices with other processors.
    bsp_sync();

    stepDetermineComponents();  // Label own matrix and shared boundaries.
    bsp_sync();                 // Communicate shared boundary components.

    stepDetermineSharedComponents();  // Determine component structure for
    bsp_sync();                       // shared components.

    // Receive segments at processor P(0) and write them to the outfile.
    stepReceiveAndWriteSegments();

    free(SEGMENTS);

    bsp_end();
}
