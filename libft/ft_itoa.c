/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnasered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:59:07 by nnasered          #+#    #+#             */
/*   Updated: 2025/08/26 12:54:25 by nnasered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	n_size(long n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	num;
	size_t	size;

	num = n;
	size = n_size(num);
	result = (char *)malloc(size + 1);
	if (!result)
		return (NULL);
	if (num < 0)
	{
		num *= -1;
		result[0] = '-';
	}
	result[size] = '\0';
	if (num == 0)
		result[0] = '0';
	while (num)
	{
		result[--size] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}
