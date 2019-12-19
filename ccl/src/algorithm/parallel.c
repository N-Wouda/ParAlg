#include "io.h"
#include "parallel/steps.h"

#include <bsp.h>


void parallel()
{
    bsp_begin(CCL_ARGUMENTS.numProcs);

    for (size_t step = 0; step != CCL_BSP_STEPS.numSteps; ++step)
    {
        CCL_BSP_STEPS.steps[step]();
        bsp_sync();
    }

    bsp_end();
}
