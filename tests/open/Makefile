SRC := $(wildcard *.c)
EXE := $(SRC:.c=)
CC := gcc

.PHONY: all
all: $(EXE)
%: %.c
	$(CC) -Wall -Werror -o $@ $<

.PHONY: clean
clean:
	rm -f $(EXE)
