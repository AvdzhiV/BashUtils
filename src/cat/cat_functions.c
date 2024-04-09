#include "cat_functions.h"

void s21_cat(FILE *fp) {
  int c = 0;
  while ((c = getc(fp)) != EOF) {
    putchar(c);
  }
}

void s21_cat_b(FILE *fp) {
  if (fp != NULL) {
    int c = 0;
    int line_counter = 1;
    int not_empty = 1;

    while ((c = getc(fp)) != EOF) {
      if (not_empty && c != '\n') {
        printf("%6d\t", line_counter);
        line_counter++;
        not_empty = 0;
      }
      putchar(c);
      if (c == '\n') not_empty = 1;
    }
  }
}

void s21_cat_e(FILE *fp) {
  if (fp != NULL) {
    int c = 0;
    while ((c = getc(fp)) != EOF) {
      if (c == '\n') {
        printf("$\n");
      } else if ((c < 32 || c == 127) && c != '\t') {
        char symbol = 0;
        if (c == 127) {
          symbol = '?';
        } else {
          symbol = '@' + c;
        }
        printf("^%c", symbol);

      } else {
        putchar(c);
      }
    }
  }
}

void s21_cat_n(FILE *fp) {
  if (fp != NULL) {
    int c = 0;
    int prev = 0;
    int line_counter = 1;

    printf("%6d\t", line_counter);
    while ((c = getc(fp)) != EOF) {
      if (prev == '\n') {
        printf("%6d\t", ++line_counter);
      }
      putchar(c);
      prev = c;
    }
  }
}

void s21_cat_s(FILE *fp) {
  int c = 0;
  int is_prev_empty = 0;
  int prev = 0;

  while ((c = getc(fp)) != EOF) {
    if (!(c == '\n' && is_prev_empty)) {
      putchar(c);
    }
    if (c == '\n' && prev == '\n') {
      is_prev_empty = 1;
    } else {
      is_prev_empty = 0;
    }
    prev = c;
  }
}

void s21_cat_t(FILE *fp) {
  if (fp != NULL) {
    int c = 0;
    while ((c = getc(fp)) != EOF) {
      if (c == '\t') {
        printf("^I");
      } else if ((c < 32 || c == 127) && c != '\n') {
        char symbol = 0;
        if (c == 127) {
          symbol = '?';
        } else {
          symbol = '@' + c;
        }
        printf("^%c", symbol);
      } else {
        putchar(c);
      }
    }
  }
}

void s21_cat_E(FILE *fp) {
  if (fp != NULL) {
    int c = 0;
    while ((c = getc(fp)) != EOF) {
      if (c == '\n') {
        printf("$\n");
      } else {
        putchar(c);
      }
    }
  }
}

void s21_cat_T(FILE *fp) {
  if (fp != NULL) {
    int c = 0;
    while ((c = getc(fp)) != EOF) {
      if (c == '\t') {
        printf("^I");
      } else {
        putchar(c);
      }
    }
  }
}