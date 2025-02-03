#ifndef S21_GREP_H
#define S21_GREP_H
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int pattern_num;
} grep_flags;

const char *short_flags = "e:ivclnhsf:o";

void parser(int argc, char *argv[], const char *short_flags,
            grep_flags *grep_opt);
void output_string(char *string, size_t str_size);
void match_print_o(regex_t *re, char *string);
void grep_logic(grep_flags grep_opt, char *filename, regex_t *re);
void reg_compile(grep_flags grep_opt, int argc, char *argv[], regex_t *re);
void add_pattern(grep_flags *grep_opt, char *pattern);
void pattern_from_file(grep_flags *grep_opt, char *filename);
#endif