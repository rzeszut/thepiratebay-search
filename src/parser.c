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

static struct tpb_parser_state_t *prepare_state(struct filter_t *filter)
{
    struct tpb_parser_state_t *state = malloc(sizeof(struct tpb_parser_state_t));
    memset(state, 0, sizeof(struct tpb_parser_state_t));

    state->filter = filter;
    state->invalid_state_error = false;

    return state;
}

struct list_t *tpb_parse_and_filter_file(FILE *in,
                                         struct filter_t *filter)
{
    char buffer[1024];
    int cread = 0;

    struct tpb_parser_state_t *state = NULL;
    struct list_t *result = NULL;
    xmlParserCtxtPtr parser_context = NULL;

    cread = fread(buffer, sizeof(char), 1024, in);
    if (cread <= 0) {
        goto exit;
    }

    state = prepare_state(filter);
    parser_context = xmlCreatePushParserCtxt(
        &tpb_sax_handler, state, buffer, cread, NULL
    );

    while ((cread = fread(buffer, sizeof(char), 1024, in)) > 0) {
        if (xmlParseChunk(parser_context, buffer, cread, 0)) {
            xmlParserError(parser_context, "Error while reading XML chunk.");
            goto exit;
        }

        if (state->invalid_state_error) {
            fputs("Invalid parser state error.", stderr);
            goto exit;
        }
    }
    xmlParseChunk(parser_context, buffer, 0, 1);

    // results found
    result = state->torrents;

exit:
    if (state) {
        if (!result) {
            list_free_with_data(state->torrents, tpb_torrent_free);
            // TODO: free current_torrent data as well?
        }
        free(state);
    }
    if (parser_context) xmlFreeParserCtxt(parser_context);
    return result;
}

