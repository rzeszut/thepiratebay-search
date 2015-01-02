#ifndef TORRENT_PRINT_H_GF7PPTCI
#define TORRENT_PRINT_H_GF7PPTCI

#include "torrent.h"
#include "list.h"

void tpb_yaml_print_torrent(FILE *out, struct tpb_torrent_t *torrent);

void tpb_yaml_print_torrents(FILE *out, struct list_t *torrents);

void tpb_xml_print_torrent(FILE *out, struct tpb_torrent_t *torrent);

void tpb_xml_print_torrents(FILE *out, struct list_t *torrents);

#endif /* end of include guard: TORRENT_PRINT_H_GF7PPTCI */
