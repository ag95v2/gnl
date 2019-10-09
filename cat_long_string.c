
#include <unistd.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE 1000000
#endif

int main()
{
	int len;
	char		 s[BUFF_SIZE];
	int i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		s[i++] = 'a';
	}
	len = 2147483647;
	
	while (len > -BUFF_SIZE)
	{
		write(1, s, BUFF_SIZE);
		len -= BUFF_SIZE;
	}
	return (0);
}
