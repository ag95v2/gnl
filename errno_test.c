
#include <errno.h>
#include <stdio.h>

int main()
{
	printf("Errno value at start: %d\n", errno);
	errno = 1;
	printf("Errno value at end: %d\n", errno);
	return (0);
}
