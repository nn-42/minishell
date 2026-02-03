/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:27:47 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/30 12:27:50 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_len(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;
	long	ln;

	ln = n;
	len = num_of_len(n);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = '\0';
	if (n == 0)
		arr[0] = '0';
	if (ln < 0)
	{
		arr[0] = '-';
		ln = -ln;
	}
	while (len-- && ln)
	{
		arr[len] = (ln % 10) + '0';
		ln /= 10;
	}
	return (arr);
}

/*
#include <stdio.h>
int main(void)
{
    printf("%s\n", ft_itoa(0));
    printf("%s\n", ft_itoa(12345));
    printf("%s\n", ft_itoa(-12345));
    printf("%s\n", ft_itoa(-2147483648));
    printf("%s\n", ft_itoa(2147483647));
    return 0;
}*/
