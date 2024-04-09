#include <getopt.h>
#include <stdio.h>

#include "cat_functions.h"

#define FLAGS 7

void file_handling(const char *filename, void (*func)(FILE *));
FILE *fileopen(const char *filename);
void arg_parser(int opt, struct flag flags[]);
void (*return_flag_func(struct flag flags[]))(FILE *);

int main(int argc, char *argv[]) {
  int opt = 0;
  int index = 0;
  int reg_flag = 0;

  const char *options = "beEnstT";

  static struct option long_options[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"squeeze-blank", 0, 0, 's'},
      {"number", 0, 0, 'n'},
      {0, 0, 0, 0},
  };

  struct flag flags[] = {
      {'b', 0, s21_cat_b}, {'e', 0, s21_cat_e}, {'E', 0, s21_cat_E},
      {'n', 0, s21_cat_n}, {'s', 0, s21_cat_s}, {'t', 0, s21_cat_t},
      {'T', 0, s21_cat_T},
  };

  while ((opt = getopt_long(argc, argv, options, long_options, &index)) != -1) {
    reg_flag = 1;
    arg_parser(opt, flags);
  }

  if (reg_flag) {
    void (*flag_func)(FILE *);
    flag_func = (*return_flag_func(flags));
    if (flag_func != NULL) {
      while (optind < argc) {
        file_handling(argv[optind++], flag_func);
      }
    }

  } else {
    while (optind < argc) {
      file_handling(argv[optind++], s21_cat);
    }
  }
  return 0;
}

FILE *fileopen(const char *filename) {
  FILE *file = fopen(filename, "rt");
  if (file == NULL) {
    printf("No such file or directory\n");
  }
  return file;
}

void file_handling(const char *filename, void (*func)(FILE *)) {
  FILE *fp = fileopen(filename);
  if (fp) {
    func(fp);
    fclose(fp);
  } else {
    return;
  }
}

void (*return_flag_func(struct flag flags[]))(FILE *) {
  void (*return_func)(FILE *) = NULL;
  for (int i = 0; i < FLAGS; i++) {
    if ((flags[i]).val == 1) {
      return_func = flags[i].func;
    }
  }
  return return_func;
}

void arg_parser(int opt, struct flag flags[]) {
  switch (opt) {
    case 'b':
      flags[0].val = 1;
      break;
    case 'e':
      flags[1].val = 1;
      break;
    case 'E':
      flags[2].val = 1;
      break;
    case 'n':
      flags[3].val = 1;
      break;
    case 's':
      flags[4].val = 1;
      break;
    case 't':
      flags[5].val = 1;
      break;
    case 'T':
      flags[6].val = 1;
      break;
    default:
      break;
  }
}
