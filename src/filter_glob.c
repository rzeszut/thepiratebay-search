#include "filter/filter_glob.h"

#include <stdlib.h>
#include <fnmatch.h>

static bool is_empty(const xmlChar *str)
{
    return (str == NULL) || (*str == 0);
}

static bool equals_xml_char(const xmlChar *ch1,
                            const xmlChar *ch2)
{
    // TODO: case-insensitive comparison
    return xmlUTF8Charcmp(ch1, ch2) == 0;
}

static bool glob_match(const xmlChar *pattern, const xmlChar *input)
{
    if (is_empty(pattern) && is_empty(input)) return true;

    if (*pattern == '?')
        return !is_empty(input) &&
            glob_match(pattern + 1, xmlUTF8Strpos(input, 1));

    if (*pattern == '*')
        return glob_match(pattern + 1, input) ||
            (!is_empty(input) &&
             glob_match(pattern, xmlUTF8Strpos(input, 1)));

    if (*pattern == '+')
        return !is_empty(input) &&
            (glob_match(pattern, xmlUTF8Strpos(input, 1)) ||
             glob_match(pattern + 1, xmlUTF8Strpos(input, 1)));

    if (*pattern == '\\')
        return !is_empty(++pattern) &&
            equals_xml_char(pattern, input) &&
            glob_match(pattern + 1, xmlUTF8Strpos(input, 1));

    return equals_xml_char(pattern, input) &&
        glob_match(pattern + 1, xmlUTF8Strpos(input, 1));
}

static bool filter_glob_match(struct filter_t *filter, const xmlChar *str)
{
    struct filter_glob_t *filter_glob = (struct filter_glob_t *) filter;
    return glob_match(filter_glob->pattern, str);
}

static void filter_glob_free(struct filter_t *filter)
{
    free(filter);
}

struct filter_t *filter_glob_create(const char *pattern)
{
    struct filter_glob_t *filter = malloc(sizeof(struct filter_glob_t));

    filter->filter.match = filter_glob_match;
    filter->filter.free = filter_glob_free;
    filter->pattern = (const xmlChar *) pattern;

    return (struct filter_t *) filter;
}


