#include "filter/filter_regex.h"

#include <stdlib.h>

static bool filter_regex_match(struct filter *filter, const char *str)
{
    struct filter_regex *filter_regex = (struct filter_regex *) filter;
    return regexec(&filter_regex->regex, str, 0, NULL, 0) == 0;
}

static void filter_regex_free(struct filter *filter)
{
    struct filter_regex *filter_regex = (struct filter_regex *) filter;
    regfree(&filter_regex->regex);
    free(filter);
}

struct filter *filter_regex_create(const char *pattern)
{
    struct filter_regex *filter = malloc(sizeof(struct filter_regex));

    filter->filter.match = filter_regex_match;
    filter->filter.free = filter_regex_free;
    regcomp(&filter->regex, pattern, REG_EXTENDED | REG_ICASE);

    return (struct filter *) filter;
}

