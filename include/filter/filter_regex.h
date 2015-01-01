#ifndef FILTER_REGEX_H_GETGR4YH
#define FILTER_REGEX_H_GETGR4YH

#include <regex.h>

#include "filter.h"

struct filter_regex {
    struct filter filter;
    regex_t regex;
};

struct filter *filter_regex_create(const char *pattern);

#endif /* end of include guard: FILTER_REGEX_H_GETGR4YH */
