#include "tpb/parser_handlers.h"
#include "tpb/parser_state.h"

#include <libxml/xmlmemory.h>

#define is_element(name, element) \
    (xmlStrcmp((name), (const xmlChar *) (element)) == 0)

static void inside_id(struct tpb_parser_state_t *state,
                      const xmlChar *str, int str_len)
{
    const xmlChar *id_str = xmlStrndup(str, str_len);
    // TODO: UTF-8 sscanf
    sscanf((const char *) id_str, "%ld", &state->current_torrent.id);
    xmlFree((void *) id_str);
}

static void inside_title(struct tpb_parser_state_t *state,
                         const xmlChar *str, int str_len)
{
    state->current_torrent.title = xmlStrndup(str, str_len);
}

static void inside_magnet(struct tpb_parser_state_t *state,
                          const xmlChar *str, int str_len)
{
    state->current_torrent.magnet = xmlStrndup(str, str_len);
}

void tpb_on_characters(void *s,
                       const xmlChar *str, int str_len)
{
    struct tpb_parser_state_t *state = s;

    switch (state->parser_state) {
    case INSIDE_ID:
        inside_id(state, str, str_len);
        break;

    case INSIDE_TITLE:
        inside_title(state, str, str_len);
        break;

    case INSIDE_MAGNET:
        inside_magnet(state, str, str_len);
        break;

    default: return;
        // ignore other characters
    }
}
