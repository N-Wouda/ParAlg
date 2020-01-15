#include "segment.h"

#include <stdio.h>


void segPrint(segment const *seg)
{
    printf("(%4zu, %4zu, [%4zu, %4zu)); [label] %8zu; [parent] %p\n",
           seg->x,
           seg->y,
           seg->zFirst,
           seg->zLast,
           seg->label,
           seg->parent);
}
