
#include "libft.h"

/* Content size is neeeded only for libft compatability */
void	del_simple(void *content, size_t content_size)
{
	if (content_size > 0)
		free(content);
}
