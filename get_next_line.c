/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:20:24 by bgian             #+#    #+#             */
/*   Updated: 2019/10/01 01:27:56 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_unread_buff	*new_buf(void)
{
	t_unread_buff	*buffer;

	buffer = (t_unread_buff *)malloc(sizeof(t_unread_buff));
	if (!buffer)
		return (0);
	buffer->data = (char *)malloc(BUFF_SIZE);
	if (!buffer->data)
	{
		free(buffer);
		return (0);
	}
	buffer->pos = 0;
	buffer->bytes_in_buff = 0;
	return (buffer);
}

// Yet only concat
static char	*concat_and_free(t_list *l, int total_len)
{
	char	*c;
	size_t	i;

	i = 0;
	c = (char *)malloc(total_len + 1);
	if (!c)
		return (0);
	while (l)
	{
		ft_memcpy(c + i, (const void *)l->content, l->content_size);
		i += l->content_size;
		l = l->next;
	}
	c[i] = 0;
	return (c);
}

/*
   Search for unread line in buffer. 
   If nothing useful found - read from fd.
   Store the result in l. Return length of string.

   Valid buffer is assumed. *l will be modified.
*/
static int	seek_nl(t_unread_buff *buff, int fd, t_list **l)
{
	int	len;
	int	total;

	total = 0;
	while (1)
	{
		len = 0;
		while (buff->pos + len < buff->bytes_in_buff && buff->data[buff->pos + len] != '\n')
			len++;
		*l = ft_lstappend(*l, ft_memdup(buff->data + buff->pos, len), len);
		
		total += len;
		if ((buff->pos += len + 1) >= buff->bytes_in_buff &&\
				(buff->bytes_in_buff = read(fd, buff->data, BUFF_SIZE)))
		{
			buff->pos = 0;
			continue;
		}
		return (total);
	}
}

int						get_next_line(const int fd, char **line)
{
	static t_unread_buff	*bufs[MAX_OPEN_FILES + 3];
	int						len;
	t_list					*l;

	l = NULL;
	if (!bufs[fd])
		bufs[fd] = new_buf();
	len = seek_nl(bufs[fd], fd, &l);
	*line = concat_and_free(l, len);
	return (len);
}
