#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_bytes(char *s) {
  printf("%s", s);
  char *p = s;
  for (; *p != '\0'; p++) {
    printf("%02x: '%c'\n", (uint8_t)*p, *p != '\n' ? *p : 'n');
  }
  printf("length: %ld\n", p - s);
}

int main(int argc, char *argv[]) {
  print_bytes("hello, 🌎!\n");

  return EXIT_SUCCESS;
}
