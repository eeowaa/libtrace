SRC := $(wildcard *.c)
EXE := $(SRC:.c=)
CC := gcc

override CFLAGS += -Wall -Werror $(and $(DEBUG),-g)

.PHONY: all
all: $(EXE)
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXE)
