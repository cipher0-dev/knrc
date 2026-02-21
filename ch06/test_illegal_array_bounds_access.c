#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int dont_access1 = 88888;
  int foo[2] = {0};
  int dont_access2 = 99999;

  printf("foo[0]: %d\n", foo[0]);
  printf("foo[1]: %d\n", foo[1]);
  printf("foo[2]: %d\n", foo[2]);
  printf("foo[-1]: %d\n", foo[-1]);
  printf("foo[-1]: %d\n", foo[-2]);

  return EXIT_SUCCESS;
}
