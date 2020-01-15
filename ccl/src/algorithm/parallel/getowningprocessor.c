#include "algorithm/parallel.h"


size_t getOwningProcessor(segment const *candidate, size_t labelSpace)
{
    return candidate->label / labelSpace;
}
