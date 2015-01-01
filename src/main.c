#include "filter/filter.h"
#include "filter/filter_substring.h"
#include "tpb/torrent.h"
#include "tpb/parser.h"

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s db-file pattern\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct filter_t *filter = filter_substring_create(argv[2]);
    struct list_t *torrents = tpb_parse_and_filter_file(argv[1], filter);

    struct list_t *it = torrents;
    while (it) {
        struct tpb_torrent_t *torrent = it->data;
        tpb_torrent_printf(stdout, torrent);

        it = it->next;
    }
    puts("...");

    list_free_with_data(torrents, tpb_torrent_free);
    filter_free(filter);

    xmlCleanupParser();

    return EXIT_SUCCESS;
}
