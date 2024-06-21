CC = g++ -Wall -Werror -Wextra -g -std=c++17
COVFLAGS = -fprofile-arcs -ftest-coverage
GTEST_LIB := $(shell pkg-config --libs gtest)
INCLUDE := $(shell pkg-config --cflags gtest)

OPENOS = vi 
ifeq ($(shell uname -s), Linux) 
	OPENOS = xdg-open 
	LCOV_GCOV = lcov --capture --directory . --output-file gcov_reportd/coverage.info --no-external 
	GENHTML = genhtml gcov_reportd/coverage.info --output-directory gcov_reportd 
endif 
ifeq ($(shell uname -s), Darwin) 
	OPENOS = open 
	LCOV_GCOV = lcov --capture --directory . --output-file gcov_reportd/coverage.info --ignore-errors source,usage,inconsistent,unused --include 's21_lib/*.h' --exclude 's21_lib/red_black_tree/rb_tree.h' 
	GENHTML = genhtml gcov_reportd/coverage.info --output-directory gcov_reportd --ignore-errors inconsistent,corrupt 
endif 
 
 
all: gcov_report 
 
gcov_report: test 
	./test 
	@mkdir -p gcov_reportd 
	$(LCOV_GCOV) 
	$(GENHTML) 
	@$(OPENOS) ./gcov_reportd/index.html

test: clean
	$(CC) $(COVFLAGS)  s21_tests/*.cpp -o test $(GTEST_LIB) $(INCLUDE) 

style:
	@cp ../materials/linters/.clang-format .
	clang-format -i s21_tests/*.cpp s21_lib/*.h ./*.h
	@rm -rf .clang-format

check_style:
	@cp ../materials/linters/.clang-format .
	clang-format -n s21_tests/*.cpp s21_lib/*.h ./*.h
	@rm -rf .clang-format

valgrind: 
	./test
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test > valgrind.log 2>&1

clean:
	@rm -rf *.out *.o *.gcov *.gcda *.gcno *.log report gcov_reportd test test.dSYM
