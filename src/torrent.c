#include "tpb/torrent.h"

#include <stdlib.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>

struct torrent_t *torrent_create(const xmlChar *id_str,
                                 const xmlChar *name,
                                 const xmlChar *magnet)
{
    struct torrent_t *torrent = malloc(sizeof(struct torrent_t));

    // TODO: UTF8 sscanf
    sscanf((const char *)id_str, "%ld", &torrent->id);

    torrent->name = xmlStrdup(name);
    torrent->magnet = xmlStrdup(magnet);

    return torrent;
}

void torrent_free(struct torrent_t *torrent)
{
    xmlFree((void *) torrent->name);
    xmlFree((void *) torrent->magnet);
    free(torrent);
}

