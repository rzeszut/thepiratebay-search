#ifndef PARSER_HANDLERS_H_WCHVCT7F
#define PARSER_HANDLERS_H_WCHVCT7F

#include <libxml/xmlstring.h>

void tpb_on_start_element(void *state,
                          const xmlChar *name,
                          const xmlChar **attrs);

void tpb_on_end_element(void *state,
                        const xmlChar *name);

void tpb_on_characters(void *state,
                       const xmlChar *str, int str_len);

#endif /* end of include guard: PARSER_HANDLERS_H_WCHVCT7F */
