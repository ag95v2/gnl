
all:

	@echo "Compiling libft"
	make -C libft/ fclean && make -C libft/ 
	@echo "Compiling gnl"
	clang -g -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c 


	@echo "Compiling test 0"
	clang -g -Wall -Wextra -Werror -I libft/includes -o main0.o -c main0.c
	clang -g -o test_gnl0 main0.o get_next_line.o -I libft/includes -L libft/ -lft

	@echo "Compiling test 1"
	clang -g -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	clang -g -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft

	@echo "Compiling test 2"
	clang -g -Wall -Wextra -Werror -I libft/includes -o main_many_lines.o -c main_many_lines.c
	clang -g -o test_gnl_many_lines main_many_lines.o get_next_line.o -I libft/includes -L libft/ -lft

	@echo "Compiling test 3 with long string"
	gcc -g  -o cat_long_string cat_long_string.c -I libft/includes -L libft/ -lft

	clang -g -I libft/includes -o test_long_string.o -c test_long_string.c
	gcc -g  -o test_long_string test_long_string.o get_next_line.o -I libft/includes -L libft/ -lft

	@echo "Compiling test with bad fd"
	gcc -g -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7 -c bad_fd.c -o bad_fd.o
	gcc -g -o bad_fd bad_fd.o get_next_line.o -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7

	@echo "Compiling test with appending after EOF"
	gcc -g -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7 -c close_append.c -o close_append.o
	gcc -g -o close_append close_append.o get_next_line.o -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7


	@echo "Compiling test with multiple files"
	gcc -g -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7 -c multiple_files.c -o multiple_files.o
	gcc -g -o multiple_files multiple_files.o get_next_line.o -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7


	@echo "Compiling test with multiple files"
	gcc -g -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7 -c multiple_files2.c -o multiple_files2.o
	gcc -g -o multiple_files2 multiple_files2.o get_next_line.o -I libft/includes/ -L libft/ -lft -DBUFFSIZE=7


test: all
	@echo "\n\nOk. Runnning tests"
	@echo "Test 0. 0 if success (Single line without end-of-line char)" 
	@valgrind  ./test_gnl0 100 > output0.txt 2> log  && cat log | grep lost 
	@diff input0.txt output0.txt | wc -l

	@echo "Test 1. 0 if success (Just random lines)" 
	@valgrind  ./test_gnl 100 > output.txt  2> log  && cat log | grep lost
	@diff input.txt output.txt | wc -l

	@echo "\n\nTest 4. Bad file descriptor. Expected error message and no memory leaks"
	valgrind  --leak-check=full ./bad_fd 2> log  && cat log | grep lost

	@echo "\n\nTest 5. Appending to file after EOF"
	valgrind  --leak-check=full ./close_append 2> log  && cat log | grep lost

	@echo "\n\nTest 6. Multiple files"
	valgrind  --leak-check=full ./multiple_files 2> log  && cat log | grep lost


	@echo "\n\nTest 7. Multiple files with bad fds"
	valgrind  --leak-check=full ./multiple_files2 2> log  && cat log | grep lost

big_test:test
	@echo "\n\nTest 2. 0 if success (Many identical small lines)" 
	@valgrind  ./test_gnl_many_lines > output1.txt  2> log  && cat log | grep lost
	@diff input1.txt output1.txt | wc -l

	@echo "\n\nTest 3. Very long string 1 0 on success and no valgrind  .roblems"
	@ ./cat_long_string | valgrind  ./test_long_string 2> log  && cat log | grep lost	
