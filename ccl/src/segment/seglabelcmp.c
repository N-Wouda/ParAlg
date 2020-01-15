#include "segment.h"


int segLabelCmp(void const *a, void const *b)
{
    segment *segA = (segment *) a;
    segment *segB = (segment *) b;

    if (segA->label < segB->label)
        return -1;

    if (segA->label == segB->label)
        return 0;

    return 1;
}
