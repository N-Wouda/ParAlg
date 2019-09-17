#include <bsp.h>
#include <stdlib.h>
#include "test.h"


int main(int argc, char **argv)
{
    bsp_init(process, argc, argv);

    process();

    return EXIT_SUCCESS;
}
