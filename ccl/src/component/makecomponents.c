#include "component.h"

#include <assert.h>

/**
 * Finds the first segment where x = target.x, y = y.target, if it exists - else
 * returns NULL.
 */
segment *find(segment *low, segment *high, segment *target);

/**
 * Merges appropriate segments in [parent, seg] in the segments array. If any
 * pointer is NULL, nothing is done.
 */
void mergeSegments(segment *seg, segment *parent);

/**
 * Checks if elem precedes target.
 */
bool isBefore(segment const *elem, segment const *target);

void makeComponents(segment *segments, size_t numSegments)
{
    for (size_t idx = 0; idx != numSegments; ++idx)
    {
        segment seg = segments[idx];

        // If this segment belongs to a component, that component must extend
        // to (x - 1, y) or (x, y - 1): those have been considered before, as
        // the segments array is ordered.
        if (seg.x > 0)
        {
            segment target = {seg.x - 1, seg.y, seg.zFirst};
            mergeSegments(&seg, find(segments, segments + idx, &target));
        }

        if (seg.y > 0)
        {
            segment target = {seg.x, seg.y - 1, seg.zFirst};
            mergeSegments(&seg, find(segments, segments + idx, &target));
        }
    }
}

void mergeSegments(segment *seg, segment *parent)
{
    if (parent == NULL || seg == NULL)  // no-op.
        return;

    assert(parent <= seg);

    size_t const x = parent->x;  // x and y to look for. These must remain
    size_t const y = parent->y;  // the same during iteration.

    while (parent != seg)
    {
        // Candidate parent starts beyond the currently considered segment,
        // or the x and y don't match up anymore: these cannot be part of the
        // same component.
        if (parent->zFirst >= seg->zLast || parent->x != x || parent->y != y)
            break;

        // Candidate parent starts before the end (above check), and ends after
        // currently considered segment. Such parents must be part of the same
        // component.
        if (parent->zLast > seg->zFirst)
            merge(seg, parent);

        parent++;
    }
}

bool isBefore(segment const *elem, segment const *target)
{
    // clang-format off
    return elem->x < target->x
        || (elem->x == target->x && elem->y < target->y)
        || (elem->x == target->x && elem->y == target->y
            && elem->zLast - 1 < target->zFirst);  // since last is exclusive.
    // clang-format on
}

segment *find(segment *low, segment *high, segment *target)
{
    while (high >= low)
    {
        segment *mid = low + (high - low) / 2;

        assert(mid >= low && mid <= high);
        segment const curr = *mid;

        // The x's and y's need to agree, and the current segment must not be
        // before the target.
        bool currEqualsTarget = curr.x == target->x && curr.y == target->y
                                && curr.zLast > target->zFirst;

        // If we're at the lower end we cannot dereference mid - 1, so this
        // check is needed here.
        if (mid == low)
            return currEqualsTarget ? mid : NULL;

        assert(mid - 1 >= low);
        segment const prev = *(mid - 1);

        // We want the first matching target, so the previous segment must be
        // different. It is not sufficient that the current segment matches the
        // target (although that is of course also needed!).
        if (isBefore(&prev, target) && currEqualsTarget)
            return mid;

        if (isBefore(&curr, target))
            low = mid + 1;
        else
            high = mid - 1;
    }

    return NULL;
}
