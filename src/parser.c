#include "tpb/parser.h"
#include "tpb/parser_state.h"
#include "tpb/parser_handlers.h"

#include <string.h>

static xmlSAXHandler tpb_sax_handler = {
    .startElement = tpb_on_start_element,
    .endElement = tpb_on_end_element,
    .characters = tpb_on_characters,
    .getEntity = tpb_on_entity,

    .error = tpb_on_error,
    .fatalError = tpb_on_error
};

struct list_t *tpb_parse_and_filter_file(const char *path,
                                         struct filter_t *filter)
{
    // initialize parser state
    struct tpb_parser_state_t state;
    memset(&state, 0, sizeof(state));
    state.filter = filter;
    state.invalid_state_error = false;

    int ret = xmlSAXUserParseFile(&tpb_sax_handler, &state, path);
    if (ret == 0) {
        return state.torrents;
    } else {
        fprintf(stderr, "Error\n");
        // in case of errors free all results
        list_free_with_data(state.torrents, torrent_free);
        // TODO: free current_torrent data as well?

        return NULL;
    }
}

