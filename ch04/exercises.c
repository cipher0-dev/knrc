#include <assert.h>
#include <stdlib.h>
#include <string.h>

void reverse_r(char *s, int start, int end) {
  if (start >= end) {
    return;
  }
  char tmp = s[end];
  s[end] = s[start];
  s[start] = tmp;
  reverse_r(s, start + 1, end - 1);
}

void reverse(char *s) { return reverse_r(s, 0, strlen(s) - 1); }

void itoa_r(int x, char *buf, int *i) {
  if (x / 10) {
    itoa_r(x / 10, buf, i);
  }
  buf[*i] = x % 10 + '0';
  *i += 1;
}

char *itoa(int x, char *buf) {
  int i = 0;
  if (x < 0) {
    x = -x;
    buf[i] = '-';
    i += 1;
  }
  itoa_r(x, buf, &i);
  buf[i] = '\0';
  return buf;
}

int main(int argc, char *argv[]) {
  char s[] = "hello world!";
  reverse(s);
  assert(!strcmp(s, "!dlrow olleh"));

  char buf[255] = {0};

  assert(!strcmp(itoa(12345, buf), "12345"));
  assert(!strcmp(itoa(-12345, buf), "-12345"));
  assert(!strcmp(itoa(0, buf), "0"));

  return EXIT_SUCCESS;
}
