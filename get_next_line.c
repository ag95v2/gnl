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

#include "libft.h"
#include "get_next_line.h"

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

/*
** 1) While there is any unread data in buff, read from buf.
** Update the state of buf.
** 2) If no '\n' found in buffer, read BINARY DATA from fd by chunks until 
** '\n' (or EOF).
** Store chunks in linked list l.
** Return their total length.
** Last chunk is always stored in "unread buffer" buff.
*/

/* TODO: CHECK ALL BOUNDARY CONDITIONS */
static size_t			seek_nl(t_unread_buff *buff, int fd, t_list *l)
{
	size_t	len;
	int		pos;
	
	pos = buff->pos;
	while (pos < buff->bytes_in_buff && buff->data[pos] == '\n')
		pos++;

	len = pos - buff->pos;
	l = ft_lstappend(l, ft_memdup(buff->data[buff->pos], len), len);
	return ((buff->pos = pos) == buff->bytes_read ?\
			buff->pos = 0, buff->bytes_read = read(fd, buff->data, BUFF_SIZE),\
			len + seek_nl(buff, fd, l) : len);
}

int						get_next_line(const int fd, char **line)
{
	static t_unread_buff	bufs[MAX_OPEN_FILES + 3];
	int						ret;

	ret = !bufs[fd] && !(bufs[fd] = new_buf()) ? -1 : filline(bufs, fd, line);
	return (ret);
}
