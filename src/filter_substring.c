#include "filter/filter_substring.h"

#include <stdlib.h>
#include <string.h>

// TODO: later add case-insensitive substring matching
static bool filter_substring_match(struct filter *filter, const char *str)
{
    struct filter_substring *filter_substr = (struct filter_substring *) filter;
    return strstr(str, filter_substr->substr) != NULL;
}

static void filter_substring_free(struct filter *filter)
{
    free(filter);
}

struct filter *filter_substring_create(const char *substr)
{
    struct filter_substring *filter = malloc(sizeof(struct filter_substring));

    filter->filter.match = filter_substring_match;
    filter->filter.free = filter_substring_free;
    filter->substr = substr;

    return (struct filter *) filter;
}

