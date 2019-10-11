
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

int main()
{
	int		fd1;
	int		fd2;
	char	*line;

	get_next_line(-123, &line);

	fd1 = open("_tmp1.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);
	fd2 = open("_tmp2.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);

	ft_putstr_fd("aaa\nbbb\n", fd1);
	ft_putstr_fd("ccc\nddd\n", fd2);
	close(fd1);
	close(fd2);


	fd1 = open("_tmp1.txt", O_RDONLY, 0666);
	fd2 = open("_tmp2.txt", O_RDONLY, 0666);

	get_next_line(fd1, &line);
	printf("Expected: 0 got: %d\n",ft_strcmp("aaa",line));
	free(line);

	get_next_line(-123, &line);

	get_next_line(fd2, &line);
	printf("Expected: 0 got: %d\n",ft_strcmp("ccc",line));
	free(line);


	get_next_line(fd2, &line);
	printf("Expected: 0 got: %d\n",ft_strcmp("ddd",line));
	free(line);

	get_next_line(fd1, &line);
	printf("Expected: 0 got: %d\n",ft_strcmp("bbb",line));
	free(line);
	return (0);
}
