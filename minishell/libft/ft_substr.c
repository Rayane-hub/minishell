/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:12:39 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 14:18:14 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	len_str;

	tmp = NULL;
	i = 0;
	len_str = ft_strlen(str);
	if (start >= len_str)
	{
		tmp = ft_calloc(1, sizeof(char));
		return (tmp);
	}
	if (len > (len_str - start))
		tmp = malloc(((len_str - start) + 1) * sizeof(char));
	else
		tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (i < (len_str - start) && i < len)
	{
		tmp[i] = str[start + i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
