#include "tpb/parser_handlers.h"
#include "tpb/parser_state.h"

#define is_element(name, element) \
    (xmlStrcmp((name), (const xmlChar *) (element)) == 0)

static void start_torrent(struct tpb_parser_state_t *state)
{
    // TODO
}

static void start_id(struct tpb_parser_state_t *state)
{
    // TODO
}

static void start_title(struct tpb_parser_state_t *state)
{
    // TODO
}

static void start_magnet(struct tpb_parser_state_t *state)
{
    // TODO
}

void tpb_on_start_element(void *s,
                          const xmlChar *name,
                          const xmlChar **attrs)
{
    struct tpb_parser_state_t *state = (struct tpb_parser_state_t *) s;

    if (is_element(name, "torrent")) {
        start_torrent(state);
    } else if (is_element(name, "id")) {
        start_id(state);
    } else if (is_element(name, "title")) {
        start_title(state);
    } else if (is_element(name, "magnet")) {
        start_magnet(state);
    } else {
        // TODO: handle unknown nodes
    }
}

