#include <complex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define PRINT_SIZEOF(type) printf("sizeof(%s): %ld\n", #type, sizeof(type))

int main(int argc, char *argv[]) {
  printf("VOID:\n");
  PRINT_SIZEOF(void);

  printf("\nINTS:\n");
  PRINT_SIZEOF(bool);
  PRINT_SIZEOF(char);
  PRINT_SIZEOF(short);
  PRINT_SIZEOF(int);
  PRINT_SIZEOF(long);
  PRINT_SIZEOF(long long);

  printf("\nFLOATS:\n");
  PRINT_SIZEOF(float);
  PRINT_SIZEOF(double);
  PRINT_SIZEOF(long double);

  printf("\nCOMPLEX:\n");
  PRINT_SIZEOF(float _Complex);
  PRINT_SIZEOF(double _Complex);
  PRINT_SIZEOF(long double _Complex);

  return EXIT_SUCCESS;
}
