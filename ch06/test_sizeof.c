#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  uint64_t foo = 123;
  printf("sizeof(int): %ld\n", sizeof(int));
  printf("sizeof(foo): %ld\n", sizeof(foo));
  printf("sizeof int: <compiler error>\n");
  printf("sizeof foo: %ld\n", sizeof foo);
  return EXIT_SUCCESS;
}
