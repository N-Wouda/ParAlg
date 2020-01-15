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

    stepSendSegments();  // Shares segments with other processors.
    bsp_sync();

    stepDetermineComponents();  // Label own matrix and shared boundaries.
    bsp_sync();                 // Communicate shared boundary components.

    stepDetermineSharedComponents();  // Determine component structure for
    stepReturnLabelledSegments();     // shared components. Sends the labelled
    bsp_sync();                       // segments to the first processor.

    // Receive segments at P(0) and write them to the outfile.
    stepReceiveAndWriteSegments();

    free(SEGMENTS);

    bsp_end();
}
