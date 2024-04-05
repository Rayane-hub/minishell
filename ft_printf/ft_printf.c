/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:46:07 by rasamad           #+#    #+#             */
/*   Updated: 2024/02/26 18:49:15 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_arg(va_list arg, const char *format)
{
	unsigned long int	nb;

	if (*format == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (*format == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr(va_arg(arg, int)));
	else if (*format == 'u')
		return (ft_print_u(va_arg(arg, unsigned int)));
	else if (*format == 'x')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (*format == 'X')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	else if (*format == 'p')
	{
		nb = va_arg(arg, unsigned long int);
		if (!nb)
			return (write(1, "(nil)", 5));
		ft_putstr("0x");
		return (ft_putnbr_base(nb, "0123456789abcdef") + 2);
	}
	else if (*format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_check_format(va_list arg, const char *format)
{
	int	check;
	int	len;

	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			check = ft_check_arg(arg, format + 1);
			if (check < 0)
				return (-1);
			len += check;
			format++;
		}
		else
		{
			if (ft_putchar((char)*format) == -1)
				return (-1);
			len++;
		}
		format++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;

	if (!format)
		return (-1);
	va_start(arg, format);
	len = ft_check_format(arg, format);
	va_end(arg);
	return (len);
}
