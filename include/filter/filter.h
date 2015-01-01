#ifndef FILTER_H_GPNX9E0J
#define FILTER_H_GPNX9E0J

#include <stdbool.h>
#include <libxml/xmlstring.h>

/**
 * Filter interface.
 */
struct filter_t {
    bool (*match)(struct filter_t *, const xmlChar *);
    void (*free)(struct filter_t *);
};

bool filter_match(struct filter_t *filter, const xmlChar *str);

void filter_free(struct filter_t *filter);

#endif /* end of include guard: FILTER_H_GPNX9E0J */
