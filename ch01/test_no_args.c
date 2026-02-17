#include <stdio.h>
#include <stdlib.h>

int print_stuff() {
  printf("stuff");
  return 1;
}

int main(int argc, char *argv[]) {
  print_stuff(123, 321);
  return EXIT_SUCCESS;
}
