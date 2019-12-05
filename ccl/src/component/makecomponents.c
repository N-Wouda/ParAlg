#include "component.h"


// TODO: this is the obvious, but slow O(n^2) implementation. This should be
// made to run in *at most* O(n log n) using .
void makeComponents(segment_t *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment_t segment = segments[idx];

        for (size_t parentIdx = 0; parentIdx != idx; ++parentIdx)
        {
            segment_t parSeg = segments[parentIdx];

            if (parSeg.x == segment.x - 1 && parSeg.y == segment.y
                && parSeg.zFirst <= segment.zFirst
                && parSeg.zLast >= segment.zFirst)
            {
                merge(segments, &segment, &parSeg);
                break;
            }

            if (parSeg.x == segment.x && parSeg.y == segment.y - 1
                && parSeg.zFirst <= segment.zFirst
                && parSeg.zLast >= segment.zFirst)
            {
                merge(segments, &segment, &parSeg);
                break;
            }
        }
    }
}
