/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:20:24 by bgian             #+#    #+#             */
/*   Updated: 2019/09/27 21:25:05 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static void				free_n_buffers(t_unread_buff *buffers, int n)
{
	while (n)
	{
		if (buffers[n])
		{
			free(buffers[n]->buff_copy);
			free(buffers[n]);
			buffers[n] = 0;
		}
		n--;
	}
}

static t_unread_buff	*new_buf(void)
{
	t_unread_buff	*buffer;

	buffer = (t_unread_buff *)malloc(sizeof(t_unread_buff));
	if (!buffer)
		return (0);
	buffer->buff_copy = (char *)malloc(BUFF_SIZE);
	if (!buff_copy)
	{
		free(buffer);
		return (0);
	}
	buffer->pos = 0;
	buffer->bytes_in_buff = 0;
	return (buffer);
}

static int				filline(t_unread_buff *bufs, int fd, char **line)
{
	int				i;
	t_unread_buff	*b;

	b = bufs[fd];
	i = 0;
	while (b->bytes_in_buff > b->pos && b->buff_copy[b->pos] != '\n')
		*line[i++] = b->buff_copy[b->pos++];

}

int	get_next_line(const int fd, char **line)
{
	static t_unread_buff	bufs[MAX_OPEN_FILES + 3];
	int						ret;

	ret = !bufs[fd] && !(bufs[fd] = new_buf()) ? -1 : filline(bufs, fd, line);
	return (ret);
}
