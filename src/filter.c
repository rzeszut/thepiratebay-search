#include "filter/filter.h"

bool filter_match(struct filter *filter, const char *str)
{
    return filter->match(filter, str);
}

void filter_free(struct filter *filter)
{
    filter->free(filter);
}

