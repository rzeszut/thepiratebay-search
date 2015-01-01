#include "tpb/parser_handlers.h"
#include "tpb/parser_state.h"

#include <stdarg.h>

xmlEntityPtr tpb_on_entity(void *s,
                           const xmlChar *name)
{
    return xmlGetPredefinedEntity(name);
}

void tpb_on_error(void *s,
                  const char *msg, ...)
{
    struct tpb_parser_state_t *state = s;
    state->invalid_state_error = true;

    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
}

