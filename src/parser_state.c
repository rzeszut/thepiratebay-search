#include "tpb/parser_state.h"

void transfer_state(struct tpb_parser_state_t *state,
                    enum tpb_xml_state from,
                    enum tpb_xml_state to)
{
    state->invalid_state_error =
        state->invalid_state_error ||
        state->parser_state != from;

    if (!state->invalid_state_error) {
        state->parser_state = to;
    }
}

