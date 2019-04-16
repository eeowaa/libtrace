### Preliminaries ###

SHELL := /bin/sh

LIBNAME := trace
LIB := lib$(LIBNAME).so

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
export UNITS := $(OBJ:.o=)

### Building ###

CC := gcc -c
LD := ld

ifdef DEBUG
CFLAGS += -g
endif

.PHONY: all
all: $(LIB)

$(LIB): $(OBJ)
	$(LD) --fatal-warnings -shared $(LDFLAGS) -o $@ $<

%.o: %.c
	$(CC) -Wall -Werror -fpic $(CFLAGS) -o $@ $<

### Testing ###

.PHONY: test
test:
	cd tests && $(MAKE) LIB=$(abspath $(LIB)) test

### Installation ###

INSTALL := /usr/bin/install -D
INSTALL_DATA := $(INSTALL) -m 644
INSTALL_PROGRAM := $(INSTALL)

PREFIX := /usr/local
LIBDIR := $(PREFIX)/lib

.PHONY: install
install:
	$(INSTALL) $(LIBDIR)/$(LIB)

.PHONY: installcheck
installcheck:
	cd tests && $(MAKE) LIB=$(LIBDIR)/$(LIB) test

### Cleanup ###

.PHONY: clean
clean:
	rm -f $(OBJ) $(LIB)
	cd tests && $(MAKE) clean

.PHONY: uninstall
uninstall:
	rm -f $(LIBDIR)/$(LIB)
