/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:40:14 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/21 14:06:10 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rev_tab(char *str, int len)
{
	int		i;
	char	temp;

	i = 0;
	len--;
	while (i <= len)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
		i++;
		len--;
	}
}

static char	*negative(int n, int len)
{
	int		unity;
	int		i;
	char	*str;

	i = 0;
	n = n * -1;
	len++;
	str = malloc(len + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (n >= 1)
	{
		unity = n % 10;
		str[i] = unity + '0';
		i++;
		n = n / 10;
	}
	str[i] = '-';
	i++;
	str[i] = 0;
	ft_rev_tab(str, len);
	return (str);
}

static char	*positive(int n, int len)
{
	int		i;
	int		unity;
	char	*str;

	i = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (n >= 1)
	{
		unity = n % 10;
		str[i] = unity + '0';
		i++;
		n = n / 10;
	}
	str[i] = 0;
	ft_rev_tab(str, len);
	return (str);
}

char	*ft_itoa(int n)
{
	int	nb;
	int	len;

	len = 0;
	nb = n;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	while (nb <= -1 || nb >= 1)
	{
		nb = nb / 10;
		len++;
	}
	if (n < 0)
		return (negative(n, len));
	else
		return (positive(n, len));
}
