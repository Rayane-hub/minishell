/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:49:56 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 14:28:00 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = (char *)str;
	while (i < n)
	{
		if (tmp[i] == (char)c)
			return ((void *)tmp + i);
		i++;
	}
	return (NULL);
}
