/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:41:03 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/11 12:33:33 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_check(char c, va_list args)
{
	if (c == 'c')
		return (printf_c(va_arg(args, int)));
	else if (c == 's')
		return (printf_s(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (printf_di(va_arg(args, int)));
	else if (c == 'u')
		return (printf_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (printf_x(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (printf_x(va_arg(args, unsigned int), 1));
	else if (c == 'p')
		return (printf_p(va_arg(args, void *)));
	else if (c == '%')
		return (printf_c('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			count += format_check(*format, args);
		}
		else if (*format == '%' && !*(format + 1))
		{
			return (-1);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
