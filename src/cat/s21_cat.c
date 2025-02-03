#include "s21_cat.h"

int main(int argc, char **argv) {
  short_opt short_flags = {0};
  char *string = NULL;
  size_t str_size = 0;
  int read = 0;
  int line_num = 1;
  int empty_string = 0;

  if (argc > 1 && parser(argc, argv, &short_flags)) {
    for (int i = optind; i < argc; ++i) {
      FILE *f = NULL;
      f = fopen(argv[i], "r");
      if (f == NULL) {
        printf("%s: %s: No such file or directory\n", argv[0], argv[i]);
        continue;
      }
      while ((read = getline(&string, &str_size, f)) != -1) {
        output(string, read, &short_flags, &line_num, &empty_string);
      }
      fclose(f);
    }
  }
  free(string);
  return 0;
}

int parser(int argc, char **argv, short_opt *short_flags) {
  int res, index, flag = 1;
  while ((res = getopt_long(argc, argv, flags, long_flags, &index)) != -1) {
    switch (res) {
      case 'b':
        short_flags->b = 1;
        break;
      case 'e':
        short_flags->e = 1;
        short_flags->v = 1;
        break;
      case 'E':
        short_flags->e = 1;
        break;
      case 'n':
        short_flags->n = 1;
        break;
      case 's':
        short_flags->s = 1;
        break;
      case 't':
        short_flags->t = 1;
        short_flags->v = 1;
        break;
      case 'T':
        short_flags->t = 1;
        break;
      case 'v':
        short_flags->v = 1;
        break;
      case '?':
        printf("usage: %s [-%s] [file ...]\n", argv[0], flags);
        flag = 0;
        break;
    }
  }
  return flag;
}

void v_flag(unsigned char *ch) {
  unsigned char x = *ch;
  if (x > 127) {
    if (x < 160) {
      printf("M-^");
    } else {
      printf("M-");
    }
  }
  if ((x < 32 && x != '\n' && x != '\t') || x == 127 || x == 255) {
    printf("^");
    *ch = (x == 127 || x == 255) ? 63 : x + 64;
  }
  if (x > 127 && x < 160) {
    *ch -= 64;
  }
  if (x > 159 && x < 255) {
    *ch -= 128;
  }
}

void output(char *string, size_t str_size, short_opt *short_flags,
            int *line_num, int *empty_string) {
  int new_line = 1;
  if (str_size < 2) {
    *empty_string += 1;
  } else {
    *empty_string = 0;
  }
  if (!short_flags->s || (short_flags->s && *empty_string < 2)) {
    unsigned char *line = (unsigned char *)string;
    for (size_t i = 0; i < str_size; ++i) {
      if (short_flags->n && !short_flags->b && new_line) {
        printf("%6d	", *line_num);
        *line_num += 1;
        new_line = 0;
      }
      if (short_flags->b && new_line && str_size > 1) {
        printf("%6d	", *line_num);
        *line_num += 1;
        new_line = 0;
      }
      if (short_flags->e && string[i] == '\n') {
        putchar('$');
      }
      if (short_flags->v) {
        v_flag(&line[i]);
      }

      if (short_flags->t && string[i] == '\t') {
        putchar('^');
        string[i] = 'I';
      }

      putchar(string[i]);
    }
  }
}
