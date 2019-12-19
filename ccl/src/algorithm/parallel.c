#include "io.h"
#include "parallel/steps.h"

#include <bsp.h>


void parallel()
{
    bsp_begin(ARGUMENTS.numProcs);

    sendMatrices();  // first processor shares submatrices to others.
    bsp_sync();

    computeLabels();  // everyone labels their own matrix and shared boundary.
    bsp_sync();

    // TODO

    receiveSegments();  // receive segments from others and write to file.

    bsp_end();
}
