#include <stdio.h>
#include <stdlib.h>

int num;

void print_num() { printf("num: %d\n", num); }

int main(int argc, char *argv[]) {
  num = 5;
  print_num();
  return EXIT_SUCCESS;
}
