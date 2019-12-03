#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stddef.h>


/**
 * Parses the passed-in command-line arguments.
 *
 * @param argc      Count of command-line arguments.
 * @param argv      Command-line arguments.
 * @param location  Data location on the file system.
 * @param numProcs  Number of processors to use.
 * @return          True if arguments were parsed successfully, false if not.
 */
bool arguments(int argc, char **argv, char **location, size_t *numProcs);

#endif  // MAIN_H
