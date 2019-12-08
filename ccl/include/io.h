#ifndef IO_H
#define IO_H

#include "segment.h"
#include "sparse.h"

/**
 * Reads a binary, sparse 3D matrix from the file system.
 *
 * See also writeSegments.
 *
 * @param location  File system location to read the matrix from.
 * @param status    True if the matrix was correctly read, false otherwise.
 * @return          The matrix read from the passed-in location.
 */
matrix readMatrix(char const *location, bool *status);

/**
 * Writes the labelled segments to the given file system location, as a sparse,
 * labelled 3D matrix.
 *
 * See also readMatrix.
 *
 * @param location      File system location to write to.
 * @param segments      Pointer to an array of segments.
 * @param numSegments   Number of segments.
 * @param numElements   Number of elements to write (not segments!).
 * @param status        True if writing completed correctly, false otherwise.
 */
void writeSegments(char const *location,
                   segment const *segments,
                   size_t numSegments,
                   size_t numElements,
                   bool *status);

#endif  // IO_H
