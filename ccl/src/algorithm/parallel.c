#include "algorithm/parallel.h"

#include "io.h"

#include <bsp.h>


void parallel()
{
    bsp_begin(ARGUMENTS.numProcs);

    sendMatrices();  // Shares sub-matrices with other processors.
    bsp_sync();

    determineComponents();  // Label own matrix and shared boundaries.
    bsp_sync();             // Communicate shared boundary components.

    determineLabels();  // Determine component structure for shared components.
    bsp_sync();

    // TODO receive all segments at first processor and write to file?

    bsp_end();
}
