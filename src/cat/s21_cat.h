#ifndef S21_CAT_H
#define S21_CAT_H

#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

char *flags = "beEnstTv";

const struct option long_flags[] = {{"number", no_argument, NULL, 'n'},
                                    {"number-nonblank", no_argument, NULL, 'b'},
                                    {"squeeze-blank", no_argument, NULL, 's'},
                                    {NULL, 0, NULL, 0}};

typedef struct short_opt {
  int b, e, n, s, t, v;
} short_opt;

int parser(int argc, char **argv, short_opt *short_flags);
void output(char *string, size_t str_size, short_opt *short_flags,
            int *line_num, int *empty_string);
void v_flag(unsigned char *ch);

#endif