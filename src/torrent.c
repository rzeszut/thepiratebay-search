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

