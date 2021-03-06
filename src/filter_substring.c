#include "filter/filter_substring.h"

#include <stdlib.h>
#include <string.h>

static bool filter_substring_match(struct filter_t *filter, const xmlChar *str)
{
    struct filter_substring_t *filter_substr =
        (struct filter_substring_t *) filter;
    // TODO boyer-moore string search algorithm?
    return xmlStrcasestr(str, filter_substr->substr) != NULL;
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
    filter->substr = BAD_CAST substr;

    return (struct filter_t *) filter;
}

