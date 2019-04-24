### Preliminaries ###

SHELL := /bin/sh

LIBNAME := trace
LIB := lib$(LIBNAME).so

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
UNITS := $(OBJ:.o=)

### Building ###

CC := gcc -c
LD := ld

override CFLAGS += -Wall -Werror -fpic $(and $(DEBUG),-g)
override LDFLAGS += --fatal-warnings -shared

.PHONY: all
all: $(LIB)

$(LIB): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

execve.o: execve.c
	$(CC) -DLIBNAME=$(LIBNAME) -DLIBDIR=$(PREFIX)/lib $(CFLAGS) -o $@ $<

### Testing ###

.PHONY: test
test:
	cd tests && $(MAKE) LIB=$(abspath $(LIB)) UNITS=$(UNITS) test

### Installation ###

INSTALL := /usr/bin/install -D
INSTALL_DATA := $(INSTALL) -m 644
INSTALL_PROGRAM := $(INSTALL)

PREFIX := /usr/local
LIBDIR := $(PREFIX)/lib

.PHONY: install
install:
	$(INSTALL) $(LIB) $(LIBDIR)/$(LIB)

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
