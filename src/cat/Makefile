SHELL := /bin/bash
FLAGS =-Wall -Wextra -Werror -std=c11
FILE=input_test.txt input_test_rus.txt non_printing.txt
FILE_TEST=input_test.txt input_test_rus.txt
CHECK=2>&1 valgrind --tool=memcheck --leak-check=yes

all: s21_cat tests
s21_cat:
	gcc $(FLAGS) s21_cat.c -o s21_cat

tests:
	diff <(./s21_cat $(FILE)) <(cat $(FILE))
	diff <(./s21_cat -E $(FILE)) <(cat -E $(FILE))
	diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	diff <(./s21_cat -T $(FILE)) <(cat -T $(FILE))
	diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	diff <(./s21_cat --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))
	diff <(./s21_cat --number-nonblank $(FILE)) <(cat --number-nonblank $(FILE))
	diff <(./s21_cat --number $(FILE)) <(cat --number $(FILE))
	diff <(./s21_cat --number --squeeze-blank --number-nonblank -e -t $(FILE)) <(cat --number --squeeze-blank --number-nonblank -e -t $(FILE))
	diff <(./s21_cat -benst $(FILE)) <(cat -benst $(FILE))

	$(CHECK) ./s21_cat -s $(FILE_TEST)
	$(CHECK) ./s21_cat -benst $(FILE_TEST)
	$(CHECK) ./s21_cat -s -n $(FILE_TEST)