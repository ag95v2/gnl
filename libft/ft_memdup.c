/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 23:17:33 by bgian             #+#    #+#             */
/*   Updated: 2019/10/01 00:03:23 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Similar to strdup, but ignores '\0' 
** Protected from malloc(0) and any kind of invalid input
*/

void	*ft_memdup(void *c, size_t n)
{
	void	*dest;

	if (!c || !n)
		return(0);
	if (dest = (void *)malloc(n))
		ft_memcpy(dest, c, n);
	return (dest);
}
