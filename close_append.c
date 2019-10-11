
#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>
#include "libft.h"

int main()
{
	int		fd;
	char	line[] = "Hello";
	char	line2[] = "Surprize, bitch!";
	char	*gnl_storage;
	int		res;

	fd = open("tmp_file_to_append.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_putstr_fd(line, fd);
	printf("FD: %d\n", fd);
	close(fd);

	fd = open("tmp_file_to_append.txt",  O_RDONLY , 0666);
	printf("FD: %d\n", fd);
	res = get_next_line(fd, &gnl_storage);

	if (res == -1)
		printf("%s\n", strerror(errno));
	printf("Gnl returned: %d\n", res);
	printf("Expected: %s\n", line);
	printf("Got: %s\n", gnl_storage);

	free(gnl_storage);
	res = get_next_line(fd, &gnl_storage);


	if (res == -1)
		printf("%s\n", strerror(errno));
	printf("Reading after EOF. Gnl returned: %d\n", res);

	close(fd);

	fd = open("tmp_file_to_append.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	ft_putstr_fd(line2, fd);
	close(fd);
	fd = open("tmp_file_to_append.txt",  O_RDONLY, 0666);
	res = get_next_line(fd, &gnl_storage);
	close(fd);

	printf("Gnl returned: %d\n", res);
	printf("Expected: %s\n", line2);
	printf("Got: %s\n", gnl_storage);

	free(gnl_storage);
	return (0);
}
