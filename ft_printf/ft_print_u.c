/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:47:36 by rasamad           #+#    #+#             */
/*   Updated: 2023/11/29 12:11:48 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_print_u(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb > 9)
		len += ft_print_u(nb / 10);
	len += ft_putchar((nb % 10) + 48);
	return (len);
}
