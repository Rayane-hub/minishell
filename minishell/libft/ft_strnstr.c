/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:16:33 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 13:15:56 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == 0)
		return ((char *)&big[i]);
	while (i < len && big[i])
	{
		while (little[j] == big[i + j])
		{
			j++;
			if (little[j] == 0 && (i + j) <= len)
				return ((char *)&big[i]);
		}
		j = 0;
		i++;
	}
	return (0);
}
