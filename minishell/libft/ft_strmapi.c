/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:53:52 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 14:17:36 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*pt;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	pt = malloc((len + 1) * sizeof(char));
	if (!pt)
		return (NULL);
	while (i < len)
	{
		pt[i] = f(i, s[i]);
		i++;
	}
	pt[i] = 0;
	return (pt);
}
