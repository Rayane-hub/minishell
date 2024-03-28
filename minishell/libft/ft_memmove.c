/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:25:30 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 13:42:07 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*tmpsrc;
	unsigned char	*tmpdst;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	tmpsrc = (unsigned char *)src;
	tmpdst = (unsigned char *)dst;
	i = 0;
	if (dst > src)
	{
		while (n--)
			tmpdst[n] = tmpsrc[n];
	}
	else
	{
		while (i < n)
		{
			tmpdst[i] = tmpsrc[i];
			i++;
		}
	}
	return (dst);
}
