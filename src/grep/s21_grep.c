#include "s21_grep.h"

int main(int argc, char *argv[]) {
  grep_flags grep_opt = {0};
  regex_t re;
  if (argc > 1) {
    parser(argc, argv, short_flags, &grep_opt);
    reg_compile(grep_opt, argc, argv, &re);
  } else {
    perror("usage: s21_grep [-e:ivclnhsf:o] PATTERN [file ...]\n");
  }
  return 0;
}

void parser(int argc, char *argv[], const char *short_flags,
            grep_flags *grep_opt) {
  int res;
  while ((res = getopt(argc, argv, short_flags)) != -1) {
    switch (res) {
      case 'e':
        grep_opt->e = 1;
        add_pattern(grep_opt, optarg);
        break;
      case 'i':
        grep_opt->i = REG_ICASE;
        break;
      case 'v':
        grep_opt->v = 1;
        break;
      case 'c':
        grep_opt->c = 1;
        break;
      case 'l':
        grep_opt->c = 1;
        grep_opt->l = 1;
        break;
      case 'n':
        grep_opt->n = 1;
        break;
      case 'h':
        grep_opt->h = 1;
        break;
      case 's':
        grep_opt->s = 1;
        break;
      case 'f':
        grep_opt->f = 1;
        pattern_from_file(grep_opt, optarg);
        break;
      case 'o':
        grep_opt->o = 1;
        break;
    }
  }
  if (grep_opt->pattern_num == 0) {
    add_pattern(grep_opt, argv[optind]);
    optind++;
  }
  if (argc - optind == 1 || (grep_opt->v && grep_opt->o)) {
    grep_opt->h = 1;
  }
}

void output_string(char *string, size_t str_size) {
  for (size_t i = 0; i < str_size; i++) {
    putchar(string[i]);
  }
  if (string[str_size - 1] != '\n') {
    putchar('\n');
  }
}

void add_pattern(grep_flags *grep_opt, char *pattern) {
  if (grep_opt->pattern_num != 0) {
    strcat(grep_opt->pattern + grep_opt->pattern_num, "|");
    grep_opt->pattern_num++;
  }
  grep_opt->pattern_num +=
      sprintf(grep_opt->pattern + grep_opt->pattern_num, "(%s)", pattern);
}

void pattern_from_file(grep_flags *grep_opt, char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    if (!grep_opt->s) {
      perror(filename);
    } else {
      return;
    }
  } else {
    char *string = NULL;
    size_t str_len = 0;
    int read;
    while ((read = getline(&string, &str_len, f)) != -1) {
      if (string[read - 1] == '\n') {
        string[read - 1] = '\0';
      }
      add_pattern(grep_opt, string);
    }
    free(string);
  }
  fclose(f);
}

void match_print_o(regex_t *re, char *string) {
  regmatch_t match;
  int res;
  int offset = 0;

  while ((res = regexec(re, string + offset, 1, &match, 0)) == 0) {
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(string[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void grep_logic(grep_flags grep_opt, char *filename, regex_t *re) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    if (!grep_opt.s) {
      perror(filename);
    } else {
      return;
    }
  }

  char *string = NULL;
  size_t str_len = 0;
  int read;
  int str_num = 1;
  int find_strings_num = 0;
  while ((read = getline(&string, &str_len, f)) != -1) {
    int res = regexec(re, string, 0, NULL, 0);
    if ((res == 0 && !grep_opt.v) || (grep_opt.v && res != 0)) {
      if (!grep_opt.c && !grep_opt.l) {
        if (!grep_opt.h) {
          printf("%s:", filename);
        }
        if (grep_opt.n) {
          printf("%d:", str_num);
        }
        if (grep_opt.o) {
          match_print_o(re, string);
        } else {
          output_string(string, read);
        }
      }
      find_strings_num++;
    }
    str_num++;
  }
  free(string);
  if (grep_opt.c && !grep_opt.l) {
    if (!grep_opt.h) {
      printf("%s:", filename);
    }
    printf("%d\n", find_strings_num);
  }
  if (grep_opt.l && find_strings_num > 0) {
    printf("%s\n", filename);
  }
  fclose(f);
}

void reg_compile(grep_flags grep_opt, int argc, char *argv[], regex_t *re) {
  int err = regcomp(re, grep_opt.pattern, grep_opt.i | REG_EXTENDED);
  if (err) {
    perror("regex compilation fail");
  }
  for (int i = optind; i < argc; i++) {
    grep_logic(grep_opt, argv[i], re);
  }
  regfree(re);
}
