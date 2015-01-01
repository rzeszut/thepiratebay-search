#ifndef FILTER_REGEX_H_GETGR4YH
#define FILTER_REGEX_H_GETGR4YH

#include <regex.h>

#include "filter.h"

struct filter_regex_t {
    struct filter_t filter;
    regex_t regex;
};

struct filter_t *filter_regex_create(const char *pattern);

#endif /* end of include guard: FILTER_REGEX_H_GETGR4YH */
