#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include "io.h"
#include "segment.h"

#include <unity.h>


/**
 * Compares the given segments for coordinate-wise equality.
 *
 * @param expected  The expected result.
 * @param actual    The actual result.
 */
void compareSegmentCoords(segment const *expected, segment const *actual);

/**
 * Obtains segments from the matrix file at the passed-in location.
 *
 * @param location      Location on the file system.
 * @param numSegments   Number of segments.
 * @return              Array of segments.
 */
segment *getExampleSegments(char const *location, size_t *numSegments);

#endif  // TESTTOOLS_H
