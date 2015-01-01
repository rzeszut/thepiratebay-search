#include "tpb/parser_handlers.h"
#include "tpb/parser_state.h"

#include <stdlib.h>
#include <string.h>
#include <libxml/xmlmemory.h>

#define is_element(name, element) \
    (xmlStrcmp((name), (const xmlChar *) (element)) == 0)

static void end_torrent(struct tpb_parser_state_t *state)
{
    transfer_state(state, INSIDE_TORRENT, NONE);
    if (state->invalid_state_error) {
        return;
    }

    bool matched = filter_match(state->filter, state->current_torrent.title);
    if (matched) {
        // if matched, copy torrent to output list
        struct torrent_t *torrent = malloc(sizeof(struct torrent_t));
        memcpy(torrent, &state->current_torrent, sizeof(struct torrent_t));
        state->torrents = list_create(torrent, state->torrents);
    } else {
        // otherwise, free strings memory
        xmlFree((void *) state->current_torrent.title);
        xmlFree((void *) state->current_torrent.magnet);
    }

    memset(&state->current_torrent, 0,  sizeof(struct torrent_t));
}

static void end_id(struct tpb_parser_state_t *state)
{
    transfer_state(state, INSIDE_ID, INSIDE_TORRENT);
}

static void end_title(struct tpb_parser_state_t *state)
{
    transfer_state(state, INSIDE_TITLE, INSIDE_TORRENT);
}

static void end_magnet(struct tpb_parser_state_t *state)
{
    transfer_state(state, INSIDE_MAGNET, INSIDE_TORRENT);
}

void tpb_on_end_element(void *s,
                        const xmlChar *name)
{
    struct tpb_parser_state_t *state = s;

    if (is_element(name, "torrent")) {
        end_torrent(state);
    } else if (is_element(name, "id")) {
        end_id(state);
    } else if (is_element(name, "title")) {
        end_title(state);
    } else if (is_element(name, "magnet")) {
        end_magnet(state);
    } else {
        // TODO: handle unknown nodes -- for extended format
    }
}

