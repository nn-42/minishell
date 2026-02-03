/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:58:14 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 10:31:29 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>

int	main(void)
{
	char dest[] = "noor faronia";
	char src[] = "hello";
	printf("dest before ft_memcpy = %s \n", dest);
	printf("src before ft_memcpy = %s \n", src);
	ft_memcpy(dest, src, 7);
	printf("dest after ft_memcpy = %s \n", dest);
	printf("src before ft_memcpy = %s \n", src);
	return (0);
}*/
