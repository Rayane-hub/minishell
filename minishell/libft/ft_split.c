/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:02:50 by rasamad           #+#    #+#             */
/*   Updated: 2024/03/24 14:08:22 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(const char *s, char c)
{
	size_t	i;
	size_t	nb_word;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			nb_word++;
			while (s[i] && s[i] != c)
				i++;
		}
		if (s[i])
			i++;
	}
	return (nb_word);
}

static void	*ft_free_split(char **res)
{
	size_t	col;

	col = 0;
	while (res[col])
		free(res[col++]);
	free(res);
	return (NULL);
}

static size_t	ft_slen(char const *s, char c)
{
	size_t	j;

	j = 0;
	while (s[j] != c && s[j])
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_word;
	char	**result;
	size_t	col;

	nb_word = ft_countword(s, c);
	col = 0;
	result = malloc((nb_word + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (col < nb_word)
	{
		while (*s == c)
			s++;
		result[col] = ft_substr(s, 0, ft_slen(s, c));
		if (!result[col])
			return (ft_free_split(result));
		s += ft_slen(s, c);
		col++;
	}
	result[col] = NULL;
	return (result);
}
