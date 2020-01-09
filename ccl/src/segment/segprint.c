#include "segment.h"

#include <stdio.h>


void segPrint(segment const *seg)
{
    printf("[coordinate] (%zu, %zu, [%zu, %zu)); [label] %zu\n",
           seg->x,
           seg->y,
           seg->zFirst,
           seg->zLast,
           seg->label);
}
