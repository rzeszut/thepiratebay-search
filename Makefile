BINDIR=bin
SRCDIR=src
INCDIR=include

CC=gcc
CCFLAGS=-c -Wall -g -I$(INCDIR) `xml2-config --cflags` -D_GNU_SOURCE
LDFLAGS=`xml2-config --libs`

SOURCES=src/main.c\
		src/list.c\
		src/xml.c\
		src/filter.c\
		src/filter_substring.c\
		src/filter_glob.c\
		src/torrent.c\
		src/torrent_print.c\
		src/parser.c\
		src/parser_state.c\
		src/parser_handlers.c\
		src/parser_handler_start.c\
		src/parser_handler_end.c\
		src/parser_handler_characters.c
EXECUTABLE=tpb-search

SOURCE_FILES=$(notdir $(SOURCES))
OBJECTS=$(addprefix $(BINDIR)/,$(SOURCE_FILES:.c=.o))

vpath %.c $(SRCDIR)

all: $(EXECUTABLE)
	@echo "Done."

$(EXECUTABLE): $(BINDIR) $(OBJECTS)
	@echo "Creating executable $(EXECUTABLE)..."
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

$(BINDIR)/%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CCFLAGS) $< -o $@

$(BINDIR):
	@echo "Creating $(BINDIR)..."
	@mkdir -p $(BINDIR)

.PHONY: clean

clean:
	@echo "Removing all binaries..."
	@$(RM) $(BINDIR)/*.o $(EXECUTABLE)
	@$(RM) -rf $(BINDIR)
	@echo "Done."

