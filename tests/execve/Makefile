CC := gcc -c
LD := ld

override CFLAGS += -Wall -Werror -fpic $(and $(DEBUG),-g)
override LDFLAGS += --fatal-warnings -shared

.PHONY: all
all: libtest.so

libtest.so: execve.o
	$(LD) $(LDFLAGS) -o $@ $<

execve.o: ../../execve.c
	$(CC) -DLIBNAME=test -DLIBDIR=$(abspath $(PWD)) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f libtest.so execve.o
