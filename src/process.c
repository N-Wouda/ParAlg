#include <bsp/bsp.h>
#include <stdio.h>
#include "test.h"


void process()
{
    bsp_begin(4);

    printf("Process %u out of %u\n", bsp_pid(), bsp_nprocs());

    bsp_end();
}
