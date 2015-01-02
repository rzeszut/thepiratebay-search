#include "tpb/torrent_print.h"
#include "xml.h"

void tpb_yaml_print_torrent(FILE *out, struct tpb_torrent_t *torrent)
{
    fprintf(out, "---\n");
    fprintf(out, "id: %ld\n", torrent->id);
    fprintf(out, "title: %s\n", torrent->title);
    fprintf(out, "magnet-link: magnet:?xt=urn:btih:%s\n", torrent->magnet);
}

void tpb_yaml_print_torrents(FILE *out, struct list_t *torrents)
{
    struct list_t *it = torrents;
    while (it) {
        struct tpb_torrent_t *torrent = it->data;
        tpb_yaml_print_torrent(out, torrent);

        it = it->next;
    }
    fputs("...", out);
}

#define newline(out) fputs("\n", (out))

void tpb_xml_print_torrent(FILE *out, struct tpb_torrent_t *torrent)
{
    TAG(out, "torrent") {
        newline(out);

        TAG(out, "id") {
            fprintf(out, "%ld", torrent->id);
        }
        newline(out);

        TAG(out, "title") {
            // TODO: properly encode entities in torrent title
            fprintf(out, "%s", torrent->title);
        }
        newline(out);

        TAG(out, "magnet") {
            fprintf(out, "%s", torrent->magnet);
        }
        newline(out);
    }
    newline(out);
}

void tpb_xml_print_torrents(FILE *out, struct list_t *torrents)
{
    fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n", out);
    fputs("<!DOCTYPE archive PUBLIC \"piratebaypoor\""
          " \"http://runn1ng.github.com/poor.dtd\">\n", out);

    TAG(out, "archive") {
        newline(out);

        struct list_t *it = torrents;
        while (it) {
            struct tpb_torrent_t *torrent = it->data;
            tpb_xml_print_torrent(out, torrent);

            it = it->next;
        }
    }
}

