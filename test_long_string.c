
#include "libft.h"

#include "get_next_line.h"
#include <stdio.h>

#include <errno.h>
#include <string.h>
int main()
{
	char	*s;
	int res;

	res = -1;
	res = get_next_line(0, &s);
	printf("Exit code: %d\n", res);

	if (res == -1 || errno)
	    printf("Something went wrong! %s\n", strerror(errno));
	if (s)
	{
		printf("Length of string is %zu\n", ft_strlen(s));
		printf("S starts with %c\n", s[0]);
	}
	free(s);
	res = get_next_line(0, &s);
	if (res == -1 || errno)
	    printf("Something went wrong! %s\n", strerror(errno));
	printf("Exit code: %d\n", res);
	return (0);
}
