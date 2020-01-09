#include "segment.h"


int segCmp(void const *a, void const *b)
{
    if (isBefore(a, b))
        return -1;

    if (isEqual(a, b))
        return 0;

    return 1;
}
