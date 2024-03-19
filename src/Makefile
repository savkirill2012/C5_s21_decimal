.PHONY: all s21_decimal.a

CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra
TEST_FLAGS=-lm
S21_DECIMAL_C=arithmetic/s21_*.c compare/s21_*.c common/s21_*.c convertors/s21_*.c other/s21_*.c
S21_DECIMAL_H=s21_*.h
S21_DECIMAL_O=*.o
TESTS=tests

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS+=-lsubunit -lgcov
endif

all: s21_decimal.a

s21_decimal.a:
	$(CC) $(S21_DECIMAL_C) -c $(FLAGS)
	ar rc s21_decimal.a $(S21_DECIMAL_O)
	ranlib s21_decimal.a

s21_covered:
	$(CC) $(S21_DECIMAL_C) -c $(FLAGS) --coverage
	ar rc s21_decimal.a $(S21_DECIMAL_O)
	ranlib s21_decimal.a

style:
	clang-format -style=google -i $(TESTS).c $(S21_DECIMAL_C) $(S21_DECIMAL_H)
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem $(TESTS).c $(S21_STRING_C) $(S21_STRING_H)

test: clean s21_covered
	$(CC) -o $(TESTS).o $(TESTS).c -c $(FLAGS) --coverage
	$(CC) $(TESTS).o s21_decimal.a -o $(TESTS) -lcheck --coverage $(FLAGS) $(TEST_FLAGS)
	./$(TESTS)

mem: test
ifeq ($(shell uname -s),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TESTS)
else
	leaks --atExit -- ./$(TESTS)
endif

clean:
	rm -rf $(S21_DECIMAL_O) s21_decimal.a $(TESTS).o $(TESTS) *.gcda *.gcno *.gcov *.info *.html report

rebuild: clean all

gcov_report: test
	lcov -t "s21_decimal" -o s21_decimal.info -c -d .
	genhtml -o report s21_decimal.info
	open report/index.html
