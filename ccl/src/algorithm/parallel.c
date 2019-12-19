#include "io.h"
#include "parallel/steps.h"

#include <bsp.h>


void parallel()
{
    bsp_begin(ARGUMENTS.numProcs);

    for (size_t step = 0; step != BSP_STEPS.numSteps; ++step)
    {
        BSP_STEPS.steps[step]();
        bsp_sync();
    }

    bsp_end();
}
