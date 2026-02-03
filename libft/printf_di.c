/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:39:08 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/11 12:33:52 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_di(int n)
{
	int				count;
	long			ln;
	char			c;

	ln = n;
	count = 0;
	if (ln < 0)
	{
		write(1, "-", 1);
		ln = -ln;
		count++;
	}
	if (ln >= 10)
		count += printf_di(ln / 10);
	c = (ln % 10) + '0';
	write(1, &c, 1);
	count++;
	return (count);
}
