/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:39:19 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/11 12:34:00 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_s(char *str)
{
	int	count;

	if (!str)
		str = "(null)";
	count = 0;
	while (str[count])
	{
		write(1, &str[count], 1);
		count++;
	}
	return (count);
}
