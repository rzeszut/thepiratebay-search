#include "filter/filter.h"
#include "filter/filter_substring.h"
#include "tpb/torrent.h"
#include "tpb/parser.h"

int main(int argc, char **argv)
{
    struct filter_t *filter = filter_substring_create("Gogol");

    struct list_t *torrents = tpb_parse_and_filter_file("db.xml", filter);

    struct list_t *it = torrents;
    while (it) {
        struct torrent_t *torrent = torrents->data;

        puts("---");
        torrent_printf(stdout, torrent);

        it = it->next;
    }
    puts("---");

    list_free_with_data(torrents, torrent_free);
    filter_free(filter);

    xmlCleanupParser();

    return 0;
}
