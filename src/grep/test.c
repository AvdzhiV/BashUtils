void exec_grep(FILE *fp, char *pattern, struct flag flags[], char *filename,
                int mult_files) {
  if (fp) {
    char line[MAX_LINE];
    int lines_counter = 0;
    int matching_lines = 0;
    int ignore_case = flags[I].val ? 1 : 0;
    regex_t regex;

    while (fgets(line, MAX_LINE, fp) != NULL) {
      char processed_line[MAX_LINE];
      strcpy(processed_line, line);
      lines_counter++;

      if (compile_regex(&regex, pattern, ignore_case)) {
        break;
      }

      if (flags[O].val && !flags[V].val) {
        grep_o(&regex, line, flags, filename, mult_files);
      } else {
        int status = regexec(&regex, processed_line, 0, NULL, 0);

        if (!status) {
          matching_lines++;
          if (flags[L].val) {
            printf("%s\n", filename);
            break;
          }
        }

        if (!flags[C].val && !flags[L].val) {
          if ((!status && !flags[V].val && !flags[N].val) ||
              (status && flags[V].val && !flags[N].val)) {
            if (!flags[H].val && mult_files) {
              printf("%s:%s", filename, line);
            } else {
              printf("%s", line);
            }
          } else if ((!status && flags[N].val && !flags[V].val) ||
                     (flags[N].val && status && flags[V].val)) {
            if (!mult_files || flags[H].val) {
              printf("%d:%s", lines_counter, line);
            } else {
              printf("%s:%d:%s", filename, lines_counter, line);
            }
          }
        }
      }
      regfree(&regex);
    }

    if (flags[C].val) {
      if (!flags[H].val && mult_files) {
        printf("%s:%d\n", filename, matching_lines);
      } else {
        printf("%d\n", matching_lines);
      }
    }
  } else {
    printf("[ERROR] Invalid file pointer.");
  }
}

int compile_regex(regex_t *regex, char *pattern, int ignore_case) {
  int result;
  if (!ignore_case) {
    result = regcomp(regex, pattern, REG_EXTENDED);
  } else {
    result = regcomp(regex, pattern, REG_EXTENDED | REG_ICASE);
  }
  if (result) {
    printf("Regex compilation error.\n");
  }
  return result;
}