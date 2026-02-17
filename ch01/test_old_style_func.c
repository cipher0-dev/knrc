#include <stdio.h>

power(base, n)
int base, n;
{
  int i, p;

  p = 1;
  for (i = 1; i <= n; ++i)
    p = p * base;
  return p;
}

main() {
  printf("power(%d, %d) == %d\n", 2, 10, power(2, 10));
  return 0;
}
