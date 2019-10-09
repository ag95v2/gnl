
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char	*s;
	int		i;
	int		fd;
	int		ret;

	fd = open("input1.txt", O_RDONLY);
	
	i = 0;
	ret = 1;
	while (ret > 0)
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
