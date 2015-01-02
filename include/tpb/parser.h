#ifndef PARSER_H_GRPJ0KC7
#define PARSER_H_GRPJ0KC7

#include <libxml/parser.h>

#include "list.h"
#include "filter/filter.h"

struct list_t *tpb_parse_and_filter_file(FILE *in,
                                         struct filter_t *filter);

#endif /* end of include guard: PARSER_H_GRPJ0KC7 */
