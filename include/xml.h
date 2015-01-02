#ifndef XML_H
#define XML_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define TAG(file, tag, ...) \
        for (__xml_tag_open = true,                                    \
             xml_print_opening_tag(file, false, tag, ##__VA_ARGS__, NULL); \
             __xml_tag_open;                                           \
             xml_print_closing_tag(file, tag), __xml_tag_open = false)

#define ETAG(file, tag, ...) \
    xml_print_opening_tag(file, true, tag, ##__VA_ARGS__, NULL)

extern bool __xml_tag_open;

/**
 * Prints a tag opening (<tag>) to the file.
 * @param file File.
 * @param closep Should the tag be closed.
 * @param tag Tag name.
 * @param ... A list of pairs "attribute", "value", terminated by NULL
 *          value.
 */
void xml_print_opening_tag(FILE *file, bool closep, const char *tag, ...);

/**
 * Prints a closing tag (</tag>) to the file.
 * @param file File.
 * @param tag Tag name.
 */
void xml_print_closing_tag(FILE *file, const char *tag);

/**
 * Prints escaped string to the file.
 * @param file File.
 * @param str String to escape.
 */
void xml_print_escaped(FILE *file, const char *str);

#endif // XML_H
