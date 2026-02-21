// This program is intended to push the limits of brk and sbrk to see how it
// behaves when we are freeing memory in the data segment that is in use by the
// program.

// Basically, sbrk will only go down so far before it stops decrecing which is
// above the address that uninitialized data is stored. Also trying to manually
// set the break lower with brk silently fails.

#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static void write_str(const char *s) {
  size_t len = 0;
  while (s[len])
    len++;
  write(1, s, len);
}

static void write_char(char c) { write(1, &c, 1); }

static void write_int(long x) {
  char buf[32];
  int i = 0;

  if (x == 0) {
    write_char('0');
    return;
  }

  if (x < 0) {
    write_char('-');
    x = -x;
  }

  while (x > 0) {
    buf[i++] = '0' + (x % 10);
    x /= 10;
  }

  while (i--) {
    write_char(buf[i]);
  }
}

static void write_hex(uintptr_t x) {
  char buf[32];
  int i = 0;

  write_str("0x");

  if (x == 0) {
    write_char('0');
    return;
  }

  while (x > 0) {
    int d = x & 0xf;
    buf[i++] = d < 10 ? '0' + d : 'a' + (d - 10);
    x >>= 4;
  }

  while (i--) {
    write_char(buf[i]);
  }
}

char foo[1 << 20];

int main(int argc, char *argv[]) {
  void *cp = sbrk(0);

  write_str("initial brk: ");
  write_hex((uintptr_t)cp);
  write_char('\n');

  for (long i = 0; i < 200000; i++) {
    write_str("i: ");
    write_int(i);
    write_char('\n');

    void *p = sbrk(-1);

    write_str("   old brk: ");
    write_hex((uintptr_t)p);
    write_char('\n');

    cp = sbrk(0);

    write_str("   new brk: ");
    write_hex((uintptr_t)cp);
    write_char('\n');

    write_str("   &foo[0]: ");
    write_hex((uintptr_t)&foo[0]);
    write_char('\n');
    write_str("    foo[0]: ");
    write_int(foo[0]);
    write_char('\n');
    write_str("  &foo[-1]: ");
    write_hex((uintptr_t)&foo[sizeof(foo) - 1]);
    write_char('\n');
    write_str("   foo[-1]: ");
    write_int(foo[sizeof(foo) - 1]);
    write_char('\n');
    write_char('\n');
  }

  write_str("attempting to brk(cp-100)\n");
  int err = brk(cp - 100);
  if (err < 0) {
    write_str("brk failed\n");
    return EXIT_FAILURE;
  }

  cp = sbrk(0);

  write_str("new cp: ");
  write_hex((uintptr_t)cp);
  write_char('\n');

  return EXIT_SUCCESS;
}
