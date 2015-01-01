#ifndef TORRENT_H_RJH8EAOW
#define TORRENT_H_RJH8EAOW

#include <libxml/xmlstring.h>

/**
 * A structure representing basic torrent data.
 */
struct torrent_t {
    long id;
    const xmlChar *name;
    const xmlChar *magnet;
};

struct torrent_t *torrent_create(const xmlChar *id_str,
                                 const xmlChar *name,
                                 const xmlChar *magnet);

void torrent_free(struct torrent_t *torrent);

#endif /* end of include guard: TORRENT_H_RJH8EAOW */
