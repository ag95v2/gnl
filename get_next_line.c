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
	buffer->nbytes = 0;
	buffer->eof = 0;
	buffer->io_err = 0;
	buffer->nl_found = 0;
	return (buffer);
}

static char	*concat_and_free(t_list **l, int total_len)
{
	char	*c;
	size_t	i;
	
	i = 0;
	c = (char *)malloc(total_len + 1);
	if (!c)
	{
		ft_lstdel(l, &del_simple);
		return (0);
	}
	while (*l)
	{
		ft_memcpy(c + i, (const void *)(*l)->content, (*l)->content_size);
		i += (*l)->content_size;
		ft_lstdelone(l, &del_simple);
	}
	c[i] = 0;
	return (c);
}

/*****************************************************************************
**		Append contents of buffer from pos to '\n' into list *l
**		Return number of bytes (len) extracted from buffer. Skip newline.
**		Update the current position of buffer to (len + 1) bytes
**		Update nl_found field if found '\n'
**
**		position can become > bytes_in_buff
*****************************************************************************/
static int	try_buffer(t_unread_buff *buff, t_list **l)
{
	int	len;

	len = 0;
	buff->nl_found = 0;
	while (buff->pos + len < buff->nbytes)
	{
		if (buff->data[buff->pos + len] == '\n')
		{
			buff->nl_found = 1;
			break;
		}
		len++;
	}
	*l = ft_lstappend(*l, ft_memdup(buff->data + buff->pos, len), len);
	buff->pos += len + 1;
	return (len);
}

/*****************************************************************************
**		First of all, try to read from buffer. 
**		If nothing interesting left in buffer, read from file.
**		If nothing interesting left in file, stop and update EOF-bit
*****************************************************************************/
static int	seek_nl(t_unread_buff *buff, int fd, t_list **l)
{
	int	total_len;

	total_len = 0;
	while (!buff->eof)
	{
		total_len += try_buffer(buff, l);
		if (buff->pos >= buff->nbytes && !buff->nl_found)
		{
			buff->nbytes = read(fd, buff->data, BUFF_SIZE);
			buff->pos = 0;
			if (buff->nbytes == 0)
				buff->eof = 1;
			if (buff->nbytes == -1)
			{
				ft_lstdel(l, &del_simple);
				return (0);
			}
			continue;
		}
		return (total_len);
	}
	return (total_len);
}

/******************************************************************************
**		Caller should not store anything useful in *line.
**		EOF handling detatils:
**		When we return 0, *line is set to NULL 
**		If EOF reached and there is still any data in buffer, reading is 
**		not considered as finished, 0 is not returned.
**		If any data is appended to file after EOF, we can read it.
**		
**		Other details:
**		1)*line IS freed and set to NULL in case of ANY errors
**		Absence of double free is guaranteed by function concat_and_free
**		2)l is ALWAYS freed in concat_and_free. 
**		Absence of double free is guaranteed by function ft_lstdel
******************************************************************************/
int						get_next_line(const int fd, char **line)
{
	static t_unread_buff	*bufs[MAX_OPEN_FILES + 3];
	int						len;
	t_list					*l;
	
	errno = 0;
	l = NULL;
	if (!bufs[fd])
		bufs[fd] = new_buf();
	if (!bufs[fd])
		return (-1);
	bufs[fd]->eof = 0;
	len = seek_nl(bufs[fd], fd, &l);
	*line = concat_and_free(&l, len);
	if (errno || bufs[fd]->eof == 1)
	{
		free(*line);
		*line = 0;
		return (errno ? -1 : 0);
	}
	return (1);
}
