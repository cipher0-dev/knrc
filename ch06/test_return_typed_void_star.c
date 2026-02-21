#include <stdio.h>
#include <stdlib.h>

struct bar {
  int x;
  double y;
  char *z;
};

// we don't explicitly cast malloc's void start to our struct type
struct bar *foo() { return malloc(sizeof(struct bar)); }

int main(int argc, char *argv[]) {
  printf("%p", foo());
  return EXIT_SUCCESS;
}
