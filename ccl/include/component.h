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
 * Finds the root element for the given candidate.
 *
 * @param candidate Candidate to find the root element for.
 * @return          Pointer to the root element.
 */
segment *findSet(segment const *candidate);

/**
 * Links two segment trees based on their rank, such that the smallest tree
 * is linked to the largest.
 *
 * See also CLRS, Introduction to Algorithms, 3rd Ed., p. 571.
 *
 * @param first     First segment to link.
 * @param second    Second segment to link.
 */
void link(segment *first, segment *second);

/**
 * Merges the sets the first and second segment belong to. This is done using
 * the link method - cf. union in CLRS.
 *
 * See also CLRS, Introduction to Algorithms, 3rd Ed., p. 571.
 *
 * @param first     First segment to link.
 * @param second    Second segment to link.
 */
void merge(segment *first, segment *second);

#endif  // COMPONENT_H
