#include "tpb/torrent.h"

#include <stdlib.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>

void tpb_torrent_free(void *t)
{
    struct tpb_torrent_t *torrent = t;

    // free copied strings
    xmlFree((void *) torrent->title);
    xmlFree((void *) torrent->magnet);

    free(torrent);
}

void tpb_torrent_printf(FILE *out, struct tpb_torrent_t *torrent)
{
    fprintf(out, "---\n");
    fprintf(out, "id: %ld\n", torrent->id);
    fprintf(out, "title: %s\n", torrent->title);
    fprintf(out, "magnet-link: magnet:?xt=urn:btih:%s\n", torrent->magnet);
}

