#include "tpb/torrent.h"

#include <stdlib.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>

void torrent_free(struct torrent_t *torrent)
{
    // free copied strings
    xmlFree((void *) torrent->title);
    xmlFree((void *) torrent->magnet);

    free(torrent);
}

void torrent_printf(FILE *out, struct torrent_t *torrent)
{
    fprintf(out, "Id: %ld\n", torrent->id);
    fprintf(out, "Title: %s\n", torrent->title);
    fprintf(out, "Magnet link: %s\n", torrent->magnet);
}

