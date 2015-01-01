#ifndef FILTER_H_GPNX9E0J
#define FILTER_H_GPNX9E0J

#include <stdbool.h>

/**
 * Filter interface.
 */
struct filter {
    bool (*match)(struct filter *, const char *);
    void (*free)(struct filter *);
};

bool filter_match(struct filter *filter, const char *str);

void filter_free(struct filter *filter);

#endif /* end of include guard: FILTER_H_GPNX9E0J */
