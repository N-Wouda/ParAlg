#ifndef MAIN_H
#define MAIN_H

#include "ccltypes.h"

#include <stdbool.h>


/**
 * Parses the passed-in command-line arguments.
 *
 * @param argc  Count of command-line arguments.
 * @param argv  Command-line arguments.
 * @return      True if arguments were parsed successfully, false if not.
 */
bool arguments(int argc, char **argv);

/**
 * Reads a binary 3D matrix from the file system.
 *
 * @param location  Location to read the matrix from on the file system.
 * @return          The matrix read from the passed-in location.
 */
matrix_t readMatrix(char *location);

#endif  // MAIN_H
