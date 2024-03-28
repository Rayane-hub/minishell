/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:11:48 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 14:27:23 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*tmp;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	tmp = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (i < len_s1)
	{
		tmp[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len_s2)
	{
		tmp[len_s1 + i] = s2[i];
		i++;
	}
	tmp[len_s1 + i] = 0;
	return (tmp);
}
