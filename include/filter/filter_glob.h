#ifndef FILTER_GLOB_H_XMDQINS3
#define FILTER_GLOB_H_XMDQINS3

#include "filter.h"

struct filter_glob_t {
    struct filter_t filter;
    const char *pattern;
};

struct filter_t *filter_glob_create(const char *pattern);

#endif /* end of include guard: FILTER_GLOB_H_XMDQINS3 */
