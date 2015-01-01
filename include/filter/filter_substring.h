#ifndef FILTER_SUBSTRING_H_0BQRRHJY
#define FILTER_SUBSTRING_H_0BQRRHJY

#include "filter.h"

struct filter_substring_t {
    struct filter_t filter;
    const char *substr;
};

struct filter_t *filter_substring_create(const char *substr);

#endif /* end of include guard: FILTER_SUBSTRING_H_0BQRRHJY */
