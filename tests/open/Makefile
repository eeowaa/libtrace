SRC := $(wildcard *.c)
EXE := $(SRC:.c=)
CC := gcc

ifdef DEBUG
CFLAGS += -g
endif

.PHONY: all
all: $(EXE)
%: %.c
	$(CC) -Wall -Werror $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXE)
