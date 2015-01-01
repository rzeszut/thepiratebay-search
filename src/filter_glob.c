#include "filter/filter_glob.h"

#include <stdlib.h>
#include <fnmatch.h>

static bool filter_glob_match(struct filter *filter, const char *str)
{
    struct filter_glob *filter_glob = (struct filter_glob *) filter;
    return fnmatch(filter_glob->pattern, str, FNM_CASEFOLD) == 0;
}

static void filter_glob_free(struct filter *filter)
{
    free(filter);
}

struct filter *filter_glob_create(const char *pattern)
{
    struct filter_glob *filter = malloc(sizeof(struct filter_glob));

    filter->filter.match = filter_glob_match;
    filter->filter.free = filter_glob_free;
    filter->pattern = pattern;

    return (struct filter *) filter;
}


