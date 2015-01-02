#include "filter/filter.h"
#include "filter/filter_substring.h"
#include "tpb/torrent_print.h"
#include "tpb/parser.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s pattern [xml-file]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *in;
    if (argc == 3) {
        in = fopen(argv[2], "r");
        if (!in) {
            fputs("Error while reading the file.", stderr);
            return EXIT_FAILURE;
        }
    } else {
        in = stdin;
    }

    struct filter_t *filter = filter_substring_create(argv[1]);

    struct list_t *torrents = tpb_parse_and_filter_file(in, filter);
    fclose(in);

    tpb_xml_print_torrents(stdout, torrents);

    list_free_with_data(torrents, tpb_torrent_free);
    filter_free(filter);

    xmlCleanupParser();
    xmlMemoryDump();

    return EXIT_SUCCESS;
}
