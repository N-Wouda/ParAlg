#include <stddef.h>


int size_t_cmp(void const *a, void const *b)
{
    size_t const first = *(size_t *) a;
    size_t const second = *(size_t *) b;

    // See e.g. https://stackoverflow.com/a/10996555/4316405
    return (first < second) ? -1 : (first > second);
}
