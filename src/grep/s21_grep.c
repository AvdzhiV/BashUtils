#include <getopt.h>
#include <regex.h>
#include <stdio.h>

#include "s21_grep_func.h"

#define FLAGS 10

FILE *fileopen(const char *filename, int flag_s);
void read_patterns_from_file(char *filename, char patterns[100][MAX_LINE],
                             int *pat_ind, int *flag_s);
void parse_options(int opt, struct flag flags[], char patterns[100][MAX_LINE],
                   int *pat_ind, int *flag_s);

int main(int argc, char *argv[]) {
  int opt = 0;
  const char *options = "e:ivclnhsf:o";

  char patterns[100][MAX_LINE];
  int pat_ind = 0;

  struct flag flags[] = {
      {'e', 0}, {'i', 0}, {'v', 0}, {'c', 0}, {'l', 0},
      {'n', 0}, {'h', 0}, {'s', 0}, {'f', 0}, {'o', 0},
  };

  int flag_s = 0;
  while ((opt = getopt(argc, argv, options)) != -1) {
    parse_options(opt, flags, patterns, &pat_ind, &flag_s);
  }

  int mult_files = 1;
  int file_ind = optind + 1;
  flag_s = flags[S].val;

  if (optind + 2 == argc && !flags[E].val && !flags[F].val) {
    mult_files = 0;
  } else if (optind + 1 == argc) {
    mult_files = 0;
  }

  if (flags[E].val || flags[F].val) {
    file_ind = optind;
  }

  while (file_ind < argc) {
    if (flags[E].val) {
      for (int i = 0; i < pat_ind; i++) {
        FILE *fp = fileopen(argv[file_ind], flag_s);
        if (fp) {
          s21_exec_grep(fp, patterns[i], flags, argv[file_ind], mult_files);
          fclose(fp);
        }
      }
    } else if (flags[F].val) {
      FILE *fp = fileopen(argv[file_ind], flag_s);
      if (fp) {
        s21_grep_f(fp, argv[file_ind], patterns, flags, pat_ind, mult_files);
        fclose(fp);
      }
    } else {
      FILE *fp = fileopen(argv[file_ind], flag_s);
      if (fp) {
        s21_exec_grep(fp, argv[optind], flags, argv[file_ind], mult_files);
        fclose(fp);
      }
    }
    file_ind++;
  }

  return 0;
}

FILE *fileopen(const char *filename, int flag_s) {
  FILE *file = fopen(filename, "rt");
  if (!file && !flag_s) {
    printf("%s: No such file or directory.\n", filename);
  }
  return file;
}

void parse_options(int opt, struct flag flags[], char patterns[100][MAX_LINE],
                   int *pat_ind, int *flag_s) {
  switch (opt) {
    case 'e':
      flags[E].val = 1;
      strcpy(patterns[*pat_ind], optarg);
      (*pat_ind)++;
      break;
    case 'i':
      flags[I].val = 1;
      break;
    case 'v':
      flags[V].val = 1;
      break;
    case 'c':
      flags[C].val = 1;
      break;
    case 'l':
      flags[L].val = 1;
      break;
    case 'n':
      flags[N].val = 1;
      break;
    case 'h':
      flags[H].val = 1;
      break;
    case 's':
      flags[S].val = 1;
      break;
    case 'f':
      flags[F].val = 1;
      read_patterns_from_file(optarg, patterns, pat_ind, flag_s);
      break;
    case 'o':
      flags[O].val = 1;
      break;
    default:
      break;
  }
}

void read_patterns_from_file(char *filename, char patterns[100][MAX_LINE],
                             int *pat_ind, int *flag_s) {
  FILE *fp = fileopen(filename, *flag_s);
  if (fp) {
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fp) != NULL) {
      strcpy(patterns[*pat_ind], line);
      (*pat_ind)++;
    }
    fclose(fp);
  }
}
