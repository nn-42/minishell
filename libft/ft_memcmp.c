/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:24:04 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 12:09:51 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*fs;
	const unsigned char	*ss;

	fs = (const unsigned char *)s1;
	ss = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (fs[i] != ss[i])
			return (fs[i] - ss[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d", ft_memcmp("noor", "noOr", 3));
	return (0);
}*/
