#include "s21_grep_func.h"

void s21_exec_grep(FILE *fp, char *pattern, struct flag flags[], char *filename,
               int mult_files) {
  if (fp) {
    char line[MAX_LINE];
    int lines_counter = 0;
    int matching_lines = 0;
    int flag_i = flags[I].val ? 1 : 0;
    regex_t regex;

    while (fgets(line, MAX_LINE, fp) != NULL) {
      char tmp_line[MAX_LINE];
      strcpy(tmp_line, line);
      lines_counter++;

      if (compile_regex(&regex, pattern, flag_i)) {
        regfree(&regex);
        break;
      }

      if (flags[O].val && !flags[V].val) {
        s21_grep_o(&regex, line, flags, filename, mult_files);
      } else {
        int status = regexec(&regex, tmp_line, 0, NULL, 0);

        if (!status) {
          matching_lines++;
          if (flags[L].val) {
            printf("%s\n", filename);
            regfree(&regex);
            break;
          }
        }

        if ((!flags[C].val) && ((!status && !flags[V].val && !flags[N].val) ||
                                (status && flags[V].val && !flags[N].val))) {
          handle_output(line, filename, flags, matching_lines, lines_counter,
                        mult_files);
        } else if ((!flags[C].val) &&
                   ((!status && flags[N].val && !flags[V].val) ||
                    (flags[N].val && status && flags[V].val))) {
          handle_output(line, filename, flags, matching_lines, lines_counter,
                        mult_files);
        }
      }
      regfree(&regex);
    }
    if (flags[C].val) {
      handle_output(line, filename, flags, matching_lines, lines_counter,
                    mult_files);
    }
  }
}

int compile_regex(regex_t *regex, char *pattern, int flag_i) {
  int result = 0;
  if (flag_i) {
    result = regcomp(regex, pattern, REG_EXTENDED | REG_ICASE);
  } else {
    result = regcomp(regex, pattern, REG_EXTENDED);
  }
  return result;
}

void s21_grep_o(regex_t *regex, char *line, struct flag flags[], char *filename,
            int mult_files) {
  int maxMatches = 10;
  regmatch_t matches[maxMatches];
  int position = 0;
  while (!regexec(regex, line + position, maxMatches, matches, 0)) {
    if (matches[0].rm_so == -1) break;
    if (!flags[H].val && mult_files) {
      printf("%s:%.*s\n", filename, (int)(matches[0].rm_eo - matches[0].rm_so),
             line + position + matches[0].rm_so);
    } else {
      printf("%.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so),
             line + position + matches[0].rm_so);
    }
    position += matches[0].rm_eo;
  }
}

void handle_output(char *line, char *filename, struct flag flags[],
                   int matching_lines, int lines_counter, int mult_files) {
  int n = flags[N].val;
  int c = flags[C].val;
  int h = flags[H].val;

  if (n) {
    if (!mult_files || h) {
      printf("%d:%s", lines_counter, line);
    } else {
      printf("%s:%d:%s", filename, lines_counter, line);
    }
  } else if (c) {
    if (!h && mult_files) {
      printf("%s:%d\n", filename, matching_lines);
    } else {
      printf("%d\n", matching_lines);
    }
  } else if (!h && mult_files) {
    printf("%s:%s", filename, line);
  } else {
    printf("%s", line);
  }
}

void s21_grep_f(FILE *fp, char *filename, char patterns[100][MAX_LINE],
            struct flag flags[], int pat_ind, int mult_files) {
  int flag_i = flags[I].val ? 1 : 0;
  regex_t *regex_array = malloc(pat_ind * sizeof(regex_t));

  int i = 0;
  while (i < pat_ind) {
    regex_t regex;
    if (!compile_regex(&regex, patterns[i], flag_i)) {
      regex_array[i] = regex;
      i++;
    }
  }

  char line[MAX_LINE];
  int status = 0;
  int matching_lines = 0;
  int lines_counter = 0;

  while (fgets(line, sizeof(line), fp) != NULL) {
    lines_counter++;
    for (int j = 0; j < pat_ind; j++) {
      if (!(status = regexec(&regex_array[j], line, 0, NULL, 0))) {
        matching_lines++;
        break;
      }
    }
    if (!status) {
      handle_output(line, filename, flags, matching_lines, lines_counter,
                    mult_files);
    }
  }

  for (int a = 0; a < pat_ind; a++) regfree(&regex_array[a]);
  free(regex_array);
}
