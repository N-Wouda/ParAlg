#ifndef COMPONENT_H
#define COMPONENT_H

#include "segment.h"


/**
 * TODO
 *
 * @param segments
 * @param numSegments
 */
void makeComponents(segment_t *segments, size_t numSegments);

/**
 * TODO
 *
 * @param segments
 * @param candidate
 * @return
 */
segment_t *findSet(segment_t *segments, segment_t *candidate);

/**
 * TODO
 *
 * @param first
 * @param second
 */
void link(segment_t *first, segment_t *second);

/**
 * TODO
 *
 * @param segments
 * @param first
 * @param second
 */
void merge(segment_t *segments, segment_t *first, segment_t *second);

#endif  // COMPONENT_H
