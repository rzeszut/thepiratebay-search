#include "tpb/parser.h"
#include "tpb/parser_state.h"
#include "tpb/parser_handlers.h"

#include <string.h>

static xmlSAXHandler tpb_sax_handler = {
    .startElement = tpb_on_start_element,
    .endElement = tpb_on_end_element,
    .characters = tpb_on_characters
};

static void free_torrent(void *t) {
    torrent_free((struct torrent_t *) t);
}

struct list_t *tpb_parse_and_filter_file(const char *path,
                                         struct filter_t *filter)
{
    struct tpb_parser_state_t state;
    memset(&state, 0, sizeof(state));
    state.filter = filter;

    int ret = xmlSAXUserParseFile(&tpb_sax_handler, &state, path);
    if (ret == 0) {
        return state.torrents;
    } else {
        // in case of errors free all results
        list_free_with_data(state.torrents, free_torrent);
        // TODO: free current_torrent data as well?

        return NULL;
    }
}

