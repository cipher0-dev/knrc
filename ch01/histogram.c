#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HORIZONTAL_COLS 100

void print_horizontal_hist(long *arr, size_t len) {
  // compute the max to scale values for output
  long max = 0;
  for (int i = 0; i < len; ++i) {
    if (arr[i] > max)
      max = arr[i];
  }

  for (int i = 0; i < len; ++i) {
    printf("%d: ", i);
    for (int j = 0; j < (HORIZONTAL_COLS * arr[i] / max); ++j)
      putchar('#');
    putchar('\n');
  }
}

#define VERTICAL_ROWS 20

void print_vertical_hist(long *arr, size_t len) {
  // compute the max to scale values for output
  long max = 0;
  for (int i = 0; i < len; ++i) {
    if (arr[i] > max)
      max = arr[i];
  }

  // initialize the output buffer
  char output[VERTICAL_ROWS][len];
  for (int i = 0; i < VERTICAL_ROWS; ++i) {
    for (int j = 0; j < len; ++j) {
      output[i][j] = ' ';
    }
  }

  // write characters to the output buffer
  for (int y = 0; y < len; ++y) {
    for (int x = VERTICAL_ROWS - 1; x >= 0; --x) {
      if (x > VERTICAL_ROWS - (VERTICAL_ROWS * arr[y] / max)) {
        output[x][y] = '#';
      }
    }
  }

  // write buffer out
  for (int i = 0; i < VERTICAL_ROWS; ++i) {
    for (int j = 0; j < len; ++j) {
      putchar(output[i][j]);
    }
    putchar('\n');
  }
  putchar('\n');
  for (int i = 0; i < len; ++i) {
    printf("%d", i % 10);
  }
  putchar('\n');
}

enum word_state {
  NOT_WORD,
  WORD,
};

bool is_word_char(char c) { return c != ' ' && c != '\n' && c != '\t'; }

int main(int argc, char *argv[]) {
  long arr[9] = {0, 1, 2, 4, 8, 4, 2, 1, 0};
  print_horizontal_hist(arr, sizeof(arr) / sizeof(arr[0]));
  print_vertical_hist(arr, sizeof(arr) / sizeof(arr[0]));

  char c;
  long c_freq[256] = {0};
  long w_len[20] = {0};
  int word_len = 0;
  enum word_state state = NOT_WORD;

  while ((c = getchar()) != EOF) {
    if (is_word_char(c) && state == NOT_WORD) {
      state = WORD;
      word_len = 1;
    } else if (is_word_char(c)) {
      word_len++;
    } else if (state == WORD) {
      w_len[word_len]++;
      state = NOT_WORD;
      word_len = 0;
    }
    c_freq[c]++;
  }

  printf("\nWord input lengths:\n");
  print_vertical_hist(w_len, sizeof(w_len) / sizeof(w_len[0]));

  printf("\nChar frequency:\n");
  print_vertical_hist(c_freq, sizeof(c_freq) / sizeof(c_freq[0]));

  return EXIT_SUCCESS;
}
