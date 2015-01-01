#ifndef FILTER_H_GPNX9E0J
#define FILTER_H_GPNX9E0J

#include <stdbool.h>

/**
 * Filter interface.
 * TODO: UTF-8 filter
 */
struct filter_t {
    bool (*match)(struct filter_t *, const char *);
    void (*free)(struct filter_t *);
};

bool filter_match(struct filter_t *filter, const char *str);

void filter_free(struct filter_t *filter);

#endif /* end of include guard: FILTER_H_GPNX9E0J */
