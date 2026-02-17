#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int nc;
  for (nc = 0; getchar() != EOF; ++nc)
    ;
  printf("%d\n", nc);
  return EXIT_SUCCESS;
}
