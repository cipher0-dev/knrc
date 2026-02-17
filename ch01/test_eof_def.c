#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void print_binary(char x) {
  for (int i = sizeof(x) * CHAR_BIT - 1; i >= 0; i--) {
    putchar((x >> i) & 1 ? '1' : '0');
  }
}

int main(int argc, char *argv[]) {
  printf("%d\n", EOF); // EOF is defined as -1
  printf("%c\n", EOF); // not a valid UTF-8 code pint
  print_binary(EOF);   // shows all 1's (2's complement)
  putchar('\n');

  return EXIT_SUCCESS;
}
