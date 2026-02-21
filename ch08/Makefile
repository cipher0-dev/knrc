.PHONY: all clean

PROG_BINS := $(patsubst %.c,build/%,$(wildcard *.c))

all: $(PROG_BINS) build/allocator_32

clean:
	-rm -rf build 2>/dev/null

# programs binaries

build/%: %.c
	mkdir -p $(@D)
	gcc -g -O0 -std=c23 -o $@ $^

build/allocator_32: allocator.c
	zig cc -target x86-linux-gnu -g -O0 -std=c23 -o $@ $^
