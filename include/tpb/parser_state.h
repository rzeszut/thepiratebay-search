#ifndef PARSER_STATE_H_6SFIWXHN
#define PARSER_STATE_H_6SFIWXHN

#include "list.h"
#include "torrent.h"
#include "filter/filter.h"

enum tpb_xml_state {
    /** Not in any element. */
    NONE = 0,

    /** Inside <torrent> element */
    INSIDE_TORRENT,

    /** Inside <id> element */
    INSIDE_ID,

    /** Inside <title> element */
    INSIDE_TITLE,

    /** Inside <magnet> element */
    INSIDE_MAGNET
};

struct tpb_parser_state_t {
    /** Current parser state */
    enum tpb_xml_state parser_state;

    /** Currently parsed torrent's data. */
    struct torrent_t current_torrent;

    /** Torrent filter. */
    struct filter_t *filter;

    /** Return value list containing all torrent matching given filter. */
    struct list_t *torrents;

    /**
     * Flag set to true when state machine went into invalid state
     * during parsing, or xml parsing error happened.
     */
    bool invalid_state_error;
};

void transfer_state(struct tpb_parser_state_t *state,
                    enum tpb_xml_state from,
                    enum tpb_xml_state to);

#endif /* end of include guard: PARSER_STATE_H_6SFIWXHN */
