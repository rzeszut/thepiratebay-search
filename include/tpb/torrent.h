#ifndef TORRENT_H_RJH8EAOW
#define TORRENT_H_RJH8EAOW

#include <libxml/xmlstring.h>
#include <stdio.h>

/**
 * A structure representing basic torrent data.
 */
struct torrent_t {
    const xmlChar *title;
    const xmlChar *magnet;
    long id;
};

void torrent_free(struct torrent_t *torrent);

void torrent_printf(FILE *out, struct torrent_t *torrent);

#endif /* end of include guard: TORRENT_H_RJH8EAOW */
