/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:02:51 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 10:44:55 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

/*
#include <stdio.h>

int	main(void)
{
	char dest[] = "noor faronia";
	char src[] = "namekmvfmkvkkl";
	printf("dest before ft_memmove : %s \n", dest);
	printf("src before ft_memmove : %s \n", src);
	ft_memmove(dest, src, 6);
	printf("dest after ft_memmove : %s \n", dest);
	printf("src after ft_memmove : %s \n", src);
	return (0);
}*/
