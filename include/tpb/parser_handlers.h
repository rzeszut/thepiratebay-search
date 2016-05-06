#ifndef PARSER_HANDLERS_H_WCHVCT7F
#define PARSER_HANDLERS_H_WCHVCT7F

#include <libxml/parser.h>
#include <string.h>

// name is a proper ascii string anyway, it does not contain any
// extended utf8 characters
#define is_element(name, element) \
    (strcmp((const char *)(name), (element)) == 0)

void tpb_on_start_element(void *state,
                          const xmlChar *name,
                          const xmlChar **attrs);

void tpb_on_end_element(void *state,
                        const xmlChar *name);

void tpb_on_characters(void *state,
                       const xmlChar *str, int str_len);

xmlEntityPtr tpb_on_entity(void *state,
                           const xmlChar *name);

void tpb_on_error(void *state,
                  const char *msg, ...);

#endif /* end of include guard: PARSER_HANDLERS_H_WCHVCT7F */
