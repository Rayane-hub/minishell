/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:48:32 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/29 12:12:01 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long int nb, char *base)
{
	int	len;

	len = 0;
	if (nb >= 16)
		len += ft_putnbr_base((nb / 16), base);
	len += ft_putchar(*(base + nb % 16));
	return (len);
}
