BINDIR=bin
SRCDIR=src
INCDIR=include

CC=gcc
CCFLAGS=-c -Wall -g -I$(INCDIR) `xml2-config --libs`
LDFLAGS=`xml2-config --cflags`

SOURCES=src/main.c
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

