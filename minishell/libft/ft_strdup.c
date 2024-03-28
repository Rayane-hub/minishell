/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:00:22 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 14:02:47 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	lensrc;
	char	*tmp;

	i = 0;
	lensrc = ft_strlen(str);
	tmp = malloc(lensrc + 1 * sizeof(char));
	if (tmp == NULL)
		return (tmp);
	while (i < lensrc)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
