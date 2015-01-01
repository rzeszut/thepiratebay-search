#include "filter/filter_substring.h"

#include <stdlib.h>
#include <string.h>

// TODO: later add case-insensitive substring matching
static bool filter_substring_match(struct filter_t *filter, const char *str)
{
    struct filter_substring_t *filter_substr =
        (struct filter_substring_t *) filter;
    return strstr(str, filter_substr->substr) != NULL;
}

static void filter_substring_free(struct filter_t *filter)
{
    free(filter);
}

struct filter_t *filter_substring_create(const char *substr)
{
    struct filter_substring_t *filter = malloc(sizeof(struct filter_substring_t));

    filter->filter.match = filter_substring_match;
    filter->filter.free = filter_substring_free;
    filter->substr = substr;

    return (struct filter_t *) filter;
}

