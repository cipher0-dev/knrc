.PHONY: all clean expanded

PROG_BINS := $(patsubst %.c,build/%,$(wildcard *.c))

all: $(PROG_BINS) build/test_int_sizes_32

clean:
	-rm -rf build 2>/dev/null

# programs binaries

build/%: %.c
	mkdir -p $(@D)
	gcc -g -O0 -o $@ $^

expanded: test_int_sizes.c
	gcc -E $^

build/test_old_style_func: test_old_style_func.c
	gcc -std=gnu89 -o $@ $^

build/test_no_args: test_no_args.c
	gcc -std=gnu89 -o $@ $^

build/test_int_sizes_32: test_int_sizes.c
	zig cc -target x86-linux-gnu -g -O0 -o $@ $^
