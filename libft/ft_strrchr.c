/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:01:30 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 13:16:03 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	lenstr;

	lenstr = 0;
	while (str[lenstr])
		lenstr++;
	while (lenstr >= 0)
	{
		if (str[lenstr] == (unsigned char)c)
			return ((char *)str + lenstr);
		lenstr--;
	}
	return (NULL);
}
