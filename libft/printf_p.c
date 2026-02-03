/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:29:58 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/11 12:33:56 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printf_h(unsigned long p)
{
	int				count;
	char			*h;
	char			c;

	count = 0;
	h = "0123456789abcdef";
	if (p >= 16)
		count += printf_h(p / 16);
	c = h[p % 16];
	write (1, &c, 1);
	count++;
	return (count);
}

int	printf_p(void *ptr)
{
	int				count;
	unsigned long	p;

	if (!ptr)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	write (1, "0x", 2);
	count = 2;
	p = (unsigned long)ptr;
	count += printf_h(p);
	return (count);
}
