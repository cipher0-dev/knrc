
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void print_binary(unsigned x) {
  int bits = sizeof(x) * 8;
  for (int i = bits - 1; i >= 0; --i) {
    putchar((x & (1u << i)) ? '1' : '0');
  }
  putchar('\n');
}

unsigned getbits(unsigned x, int p, int n) {
  // x = 01010101
  // p = 5
  // n = 4

  // 11111111 ~0
  // 11110000 (~0 << n)
  // 11110000 (~0 << n)
  // 00001111 ~(~0 << n)   # how many bits to read

  // 2        (p + 1 - n)  # how many bits to drop off RHS

  // 01010101 x
  // 00010101 (x >> (p + 1 - n))  # drop off the bits

  // 00001111 ~(~0 << n)
  // 00010101 (x >> (p + 1 - n))
  // 00000101 (x >> (p + 1 - n)) & ~(~0 << n)

  return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned rightrot(unsigned x, int n) {
  return (x >> n) | (x << (sizeof(x) * 8 - n));
}
unsigned leftrot(unsigned x, int n) {
  return (x << n) | (x >> (sizeof(x) * 8 - n));
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
  unsigned mask = ~(~0 << n);
  unsigned rotated = rightrot(x, p + 1 - n);
  unsigned a = y & mask;
  unsigned b = rotated & ~mask;
  unsigned prerotated = a | b;
  return leftrot(prerotated, p + 1 - n);
}

unsigned invert(unsigned x, int p, int n) {
  unsigned mask = ~(~0 << n);
  unsigned rotated = rightrot(x, p + 1 - n);
  unsigned prerotated = rotated ^ mask;
  return leftrot(prerotated, p + 1 - n);
}

unsigned bitcount(unsigned x) {
  int b;
  for (b = 0; x != 0; x &= (x - 1))
    b++;
  return b;
}

int main(int argc, char *argv[]) {
  assert(getbits(75, 4, 3) == 2);
  assert(getbits(85, 5, 4) == 5);
  assert(setbits(85, 5, 4, 170) == 105);
  assert(rightrot(3, 2) == 3221225472);
  assert(leftrot(3221225472, 2) == 3);
  assert(invert(255, 5, 4) == 195);
  assert(invert(255, 6, 3) == 143);
  assert(bitcount(12) == 2);
  assert(bitcount(112) == 3);
  assert(bitcount(-112) == 26);
  return EXIT_SUCCESS;
}
