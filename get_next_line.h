/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:18:19 by bgian             #+#    #+#             */
/*   Updated: 2019/09/30 23:38:18 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# define MAX_OPEN_FILES 1024
# define BUFF_SIZE 32

typedef struct	s_unread_buff
{
	char		*data;
	int			pos;
	int			bytes_in_buff;
}				t_unread_buff;

int	get_next_line(const int fd, char **line);

#endif
