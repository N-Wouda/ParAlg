#include "component.h"


// TODO: binary search on the prevX and currX members of the segments.
void makeComponents(segment *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = segments[idx];

        for (size_t parentIdx = 0; parentIdx != idx; ++parentIdx)
        {
            segment par = segments[parentIdx];

            // (x - 1, same y, matching z).
            if (par.x == seg.x - 1 && par.y == seg.y && par.zFirst <= seg.zFirst
                && par.zLast >= seg.zFirst)
                merge(segments, &seg, &par);

            // (same x, y - 1, matching z).
            if (par.x == seg.x && par.y == seg.y - 1 && par.zFirst <= seg.zFirst
                && par.zLast >= seg.zFirst)
                merge(segments, &seg, &par);
        }
    }
}
