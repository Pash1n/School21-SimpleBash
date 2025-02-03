SHELL := /bin/bash
FLAGS =-Wall -Wextra -Werror -std=c11
FILE1=input_test1.txt
FILE2=input_test1.txt input_test2.txt
FILE3=input_test1.txt input_test2.txt input_test3.txt
PATTERN1=pattern_1.txt
PATTERN2=pattern_2.txt
NONEXIST=no_file.txt
CHECK=2>&1 valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all




all: s21_grep tests
s21_grep:
	gcc $(FLAGS) s21_grep.c -o s21_grep

tests:
	diff <(./s21_grep abc $(FILE1)) <(grep abc $(FILE1))
	diff <(./s21_grep abc $(FILE2)) <(grep abc $(FILE2))
	diff <(./s21_grep abc $(FILE3)) <(grep abc $(FILE3))
	diff <(./s21_grep -e abc $(FILE1)) <(grep -e abc $(FILE1))
	diff <(./s21_grep -e abc $(FILE3)) <(grep -e abc $(FILE3))
	diff <(./s21_grep -e abc -e 111 $(FILE2)) <(grep -e abc -e 111 $(FILE2))
	diff <(./s21_grep -i AbC $(FILE1)) <(grep -i AbC $(FILE1))
	diff <(./s21_grep -i AbC $(FILE2)) <(grep -i AbC $(FILE2))
	diff <(./s21_grep -v AbC $(FILE2)) <(grep -v AbC $(FILE2))
	diff <(./s21_grep -c abc $(FILE2)) <(grep -c abc $(FILE2))
	diff <(./s21_grep -c 222 $(FILE3)) <(grep -c 222 $(FILE3))
	diff <(./s21_grep -l abc $(FILE1)) <(grep -l abc $(FILE1))
	diff <(./s21_grep -l 222 $(FILE2)) <(grep -l 222 $(FILE2))
	diff <(./s21_grep -n abc $(FILE1)) <(grep -n abc $(FILE1))
	diff <(./s21_grep -n 222 $(FILE3)) <(grep -n 222 $(FILE3))
	diff <(./s21_grep -h abc $(FILE1)) <(grep -h abc $(FILE1))
	diff <(./s21_grep -h 222 $(FILE3)) <(grep -h 222 $(FILE3))
	diff <(./s21_grep -s abc $(FILE1) $(NONEXIST)) <(grep -s abc $(FILE1) $(NONEXIST))
	diff <(./s21_grep -s abc $(FILE2) $(NONEXIST)) <(grep -s abc $(FILE2) $(NONEXIST))
	diff <(./s21_grep -f $(PATTERN1) $(FILE1)) <(grep -f $(PATTERN1) $(FILE1))
	diff <(./s21_grep -f $(PATTERN1) -f $(PATTERN2) $(FILE2)) <(grep -f $(PATTERN1) -f $(PATTERN2) $(FILE2))
	diff <(./s21_grep -o AbC $(FILE3)) <(grep -o AbC $(FILE3))
	diff <(./s21_grep -o abc $(FILE1)) <(grep -o abc $(FILE1))
	diff <(./s21_grep -iv -f $(PATTERN1) $(FILE2)) <(grep -iv -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -ic -f $(PATTERN1) $(FILE2)) <(grep -ic -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -il -f $(PATTERN1) $(FILE2)) <(grep -il -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -in -f $(PATTERN1) $(FILE2)) <(grep -in -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -ih -f $(PATTERN1) $(FILE2)) <(grep -ih -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -is -f $(PATTERN1) $(FILE2)) <(grep -is -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -io -f $(PATTERN1) $(FILE2)) <(grep -io -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -vi -f $(PATTERN1) $(FILE2)) <(grep -vi -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -vc -f $(PATTERN1) $(FILE2)) <(grep -vc -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -vl -f $(PATTERN1) $(FILE2)) <(grep -vl -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -vn -f $(PATTERN1) $(FILE2)) <(grep -vn -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -vh -f $(PATTERN1) $(FILE2)) <(grep -vh -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -vs -f $(PATTERN1) $(FILE2)) <(grep -vs -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -vo -f $(PATTERN1) $(FILE2)) <(grep -vo -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -cl -f $(PATTERN1) $(FILE2)) <(grep -cl -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -cn -f $(PATTERN1) $(FILE2)) <(grep -cn -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -ch -f $(PATTERN1) $(FILE2)) <(grep -ch -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -cs -f $(PATTERN1) $(FILE2)) <(grep -cs -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -co -f $(PATTERN1) $(FILE2)) <(grep -co -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -ln -f $(PATTERN1) $(FILE2)) <(grep -ln -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -lh -f $(PATTERN1) $(FILE2)) <(grep -lh -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -ls -f $(PATTERN1) $(FILE2)) <(grep -ls -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -lo -f $(PATTERN1) $(FILE2)) <(grep -lo -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -nh -f $(PATTERN1) $(FILE2)) <(grep -nh -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -ns -f $(PATTERN1) $(FILE2)) <(grep -ns -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -no -f $(PATTERN1) $(FILE2)) <(grep -no -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -hs -f $(PATTERN1) $(FILE2)) <(grep -hs -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -ho -f $(PATTERN1) $(FILE2)) <(grep -ho -f $(PATTERN1) $(FILE2))
	diff <(./s21_grep -so -f $(PATTERN1) $(FILE2)) <(grep -so -f $(PATTERN1) $(FILE2))

	$(CHECK) ./s21_grep abc $(FILE1)
	$(CHECK) ./s21_grep -f $(PATTERN1) -f $(PATTERN2) $(FILE2)
	$(CHECK) ./s21_grep -e abc -e 111 $(FILE2)

	