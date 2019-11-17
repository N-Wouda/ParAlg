#include "main.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    if (!arguments(argc, argv))
        return EXIT_FAILURE;

    matrix_t mat = readMatrix("somewhere");

    segment(&mat);

    return EXIT_SUCCESS;
}
