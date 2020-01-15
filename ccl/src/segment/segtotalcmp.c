#include "segment.h"


int segTotalCmp(void const *a, void const *b)
{
    int cmp = segCoordCmp(a, b);

    if (cmp != 0)
        return cmp;

    return segLabelCmp(a, b);
}
