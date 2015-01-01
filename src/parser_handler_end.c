#include "tpb/parser_handlers.h"
#include "tpb/parser_state.h"

#define is_element(name, element) \
    (xmlStrcmp((name), (const xmlChar *) (element)) == 0)

static void end_torrent(struct tpb_parser_state_t *state)
{
    // TODO
}

static void end_id(struct tpb_parser_state_t *state)
{
    // TODO
}

static void end_title(struct tpb_parser_state_t *state)
{
    // TODO
}

static void end_magnet(struct tpb_parser_state_t *state)
{
    // TODO
}

void tpb_on_end_element(void *s,
                        const xmlChar *name)
{
    struct tpb_parser_state_t *state = (struct tpb_parser_state_t *) s;

    if (is_element(name, "torrent")) {
        end_torrent(state);
    } else if (is_element(name, "id")) {
        end_id(state);
    } else if (is_element(name, "title")) {
        end_title(state);
    } else if (is_element(name, "magnet")) {
        end_magnet(state);
    } else {
        // TODO: handle unknown nodes
    }
}

