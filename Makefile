
all:

	@echo "Compiling libft"
	make -C libft/ fclean && make -C libft/
	@echo "Compiling gnl"
	clang -g -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	clang -g -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	@echo "Compiling test 1"
	clang -g -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft


	@echo "Compiling test 2"
	clang -g -Wall -Wextra -Werror -I libft/includes -o main_many_lines.o -c main_many_lines.c
	clang -g -o test_gnl_many_lines main_many_lines.o get_next_line.o -I libft/includes -L libft/ -lft

	@echo "Compiling test 3 with long string"
	gcc -g  -o cat_long_string cat_long_string.c -I libft/includes -L libft/ -lft

	clang -g -I libft/includes -o test_long_string.o -c test_long_string.c
	gcc -g  -o test_long_string test_long_string.o get_next_line.o -I libft/includes -L libft/ -lft

	@echo "Compiling test with bad fd"
	gcc -g bad_fd.c -o bad_fd -I libft/includes/ -L libft/ -lft
	
	@echo "\n\nOk. Runnning tests"
	@echo "Test 1. 0 if success (Just random lines)" 
	@valgrind ./test_gnl 100 > output.txt 
	@diff input.txt output.txt | wc -l


	@echo "\n\nTest 2. 0 if success (Many identical small lines)" 
	@valgrind ./test_gnl_many_lines > output1.txt 
	@diff input1.txt output1.txt | wc -l

	@echo "\n\nTest 3. Very long string 1 0 on success and no valgrind problems"
	@ ./cat_long_string | valgrind ./test_long_string	

	@echo "\n\nTest 4. Bad file descriptor. Expected error message and no memory leaks"
	valgrind ./bad_fd

