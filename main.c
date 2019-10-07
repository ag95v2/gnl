
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_NLINES 3 

int main(int argc, char **argv)
{
	char	*s;
	int		i;
	int		nlines;
	int		fd;
	int		len;

	fd = open("input.txt", O_RDONLY);
	nlines = argc > 1 ? ft_atoi(argv[1]) : DEFAULT_NLINES;
	
	i = 0;
	while (i++ < nlines)
	{
		len =  get_next_line(fd, &s);
		//printf("Line number %d contains %d bytes\n", i, len);
		if (strlen(s))
			printf("%s\n", s);
	}
	return (0);
}
