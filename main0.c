
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_NLINES 100 

int main(int argc, char **argv)
{
	char	*s;
	int		i;
	int		nlines;
	int		fd;
	int		ret;

	fd = open("input0.txt", O_RDONLY);
	nlines = argc > 1 ? ft_atoi(argv[1]) : DEFAULT_NLINES;
	
	i = 0;
	ret = 1;
	while (i++ < nlines && ret > 0)
	{
		if ((ret = get_next_line(fd, &s)) > 0)
		{
			printf("%s\n", s);
			free(s);
		}
	}
	close(fd);

	return (0);
}
