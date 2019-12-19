#include "parallel/steps.h"

#include <bsp.h>


void computeLabels()
{
    unsigned int messages;
    bsp_qsize(&messages, NULL);

    if (messages != 3)
        bsp_abort("%u: expected 3 messages, got %u.\n", bsp_pid(), messages);

    enum tag recTag;
    size_t messageSize;
    bsp_get_tag(&messageSize, &recTag);

    switch (recTag)
    {
        case X:
            bsp_abort("HelloX\n");
            return;
        case Y:
            bsp_abort("HelloY\n");
            return;
        case Z:
            bsp_abort("HelloZ\n");
            return;
        default:
            bsp_abort("Message tag not understood.\n");
    }
}
