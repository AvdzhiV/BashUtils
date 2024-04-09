#ifndef S21_GREP_FUNCTIONS_H
#define S21_GREP_FUNCTIONS_H
#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_FNAME 100

struct flag {
  char name;
  int val;
};

enum flags_index{E, I, V, C, L, N, H, S, F, O};

void s21_exec_grep(FILE *fp, char *pattern, struct flag flags[], char *filename,
                int mult_files);
int compile_regex(regex_t *regex, char *pattern, int ignore_case);
void s21_grep_o(regex_t *regex, char *line, struct flag flags[], char *filename,
            int mult_files);
void handle_output(char *line, char *filename, struct flag flags[], int matching_lines,
            int lines_counter, int mult_files);
void s21_grep_f(FILE *fp, char *filename, char patterns[100][MAX_LINE],
            struct flag flags[], int pat_ind, int mult_files);

#endif
