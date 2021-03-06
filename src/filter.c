#include "filter/filter.h"

bool filter_match(struct filter_t *filter, const xmlChar *str)
{
    return filter->match(filter, str);
}

void filter_free(struct filter_t *filter)
{
    filter->free(filter);
}

