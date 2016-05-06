#include "filter/filter_glob.h"

#include <stdlib.h>
#include <fnmatch.h>
#include <ctype.h>

inline static bool is_empty(const xmlChar *str)
{
    return (str == NULL) || (*str == 0);
}

inline static bool equals_utf8_char(const xmlChar *c1,
                                    const xmlChar *c2)
{
    int size = xmlUTF8Size(c1);

    while (size-- > 0 && *c2 != 0)
        if (*c1++ != *c2++)
            return false;

    return true;
}

static bool equals_xml_char(const xmlChar *c1, const xmlChar *c2,
                            bool c1_empty, bool c2_empty)
{
    if (c1_empty || c2_empty) return false;

    return tolower(*c1) == tolower(*c2) ||
        equals_utf8_char(c1, c2);
}

static bool glob_match(const xmlChar *pattern, const xmlChar *input)
{
    const bool pattern_empty = is_empty(pattern);
    const bool input_empty = is_empty(input);

    if (pattern_empty && input_empty) return true;

    if (*pattern == '?')
        return !input_empty &&
            glob_match(pattern + 1, xmlUTF8Strpos(input, 1));

    if (*pattern == '*')
        return glob_match(pattern + 1, input) ||
            (!input_empty &&
             glob_match(pattern, xmlUTF8Strpos(input, 1)));

    if (*pattern == '+')
        return !input_empty &&
            (glob_match(pattern, xmlUTF8Strpos(input, 1)) ||
             glob_match(pattern + 1, xmlUTF8Strpos(input, 1)));

    if (*pattern == '\\')
        return !is_empty(++pattern) &&
            equals_xml_char(pattern, input, pattern_empty, input_empty) &&
            glob_match(pattern + 1, xmlUTF8Strpos(input, 1));

    return equals_xml_char(pattern, input, pattern_empty, input_empty) &&
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


