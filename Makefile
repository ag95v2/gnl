
all:
	make -C libft/ fclean && make -C libft/
	clang -g -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
	clang -g -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
	clang -g -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
	@echo "\n\nOk. Runnning tests"
	@echo "Test 1. 0 if success" 
	@./test_gnl 100 > output.txt
	@diff input.txt output.txt | wc -l
