
#include "get_next_line.c"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "errno.h"

int main()
{
	int res;
	char c[10];
	int fd;
	char *s;

	res = get_next_line(100, &s);
	printf("Read from random closed fd, result: %d\n", res);
	printf("Error: %s\n", strerror(errno));

	//close(1);
	//close(2);
	//fd = open("bad_fd_output.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	//ft_putstr_fd(ft_itoa(fd), fd);

	//res = read(2, c, 5);
	//printf("Read from stderr, result: %d\n", res);
	
	return (0);
}
