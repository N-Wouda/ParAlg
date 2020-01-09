#ifndef COMPONENT_H
#define COMPONENT_H

#include "segment.h"


/**
 * Labels the passed-in set of segments, such that each belong to a tree of
 * neighbouring segments, where each has a distinct label.
 *
 * @param segments      Pointer to an array of segments.
 * @param numSegments   Number of segments.
 */
void makeComponents(segment *segments, size_t numSegments);

/**
 * Finds the root element of the set the given candidate belongs to, and
 * assigns all parent nodes to this root. Uses an efficient one-pass path
 * halving method, due to Tarjan and Van Leeuwen (1984).
 *
 * References:
 *  - CLRS, Introduction to Algorithms, 3rd Ed., ch. 21.
 *  - Tarjan and Van Leeuwen, "Worst-case Analysis of Set Union Algorithms",
 *    J. ACM, 1984, pp. 245-281.
 *
 * @param candidate Candidate to find the root element for.
 * @return          Pointer to the root element.
 */
segment *findSet(segment *candidate);

/**
 * Tests if the candidate segment is a component root.
 *
 * @param candidate Candidate root segment.
 * @return          True when the root's parent points to itself, false if not.
 */
bool isRoot(segment const *candidate);

/**
 * Relabels the passed-in segments with their root segment's label.
 *
 * @param segments      Segments to (re)label.
 * @param numSegments   Number of segments.
 */
void labelSegments(segment *segments, size_t numSegments);

/**
 * Links two segment trees based on their rank, such that the smallest tree
 * is linked to the largest.
 *
 * See also CLRS, Introduction to Algorithms, 3rd Ed., ch. 21.
 *
 * @param first     First segment to link.
 * @param second    Second segment to link.
 */
void link(segment *first, segment *second);

/**
 * Merges the sets the first and second segment belong to. This is done using
 * the link method - cf. union in CLRS.
 *
 * See also CLRS, Introduction to Algorithms, 3rd Ed., ch. 21.
 *
 * @param first     First segment to link.
 * @param second    Second segment to link.
 */
void merge(segment *first, segment *second);

#endif  // COMPONENT_H
