/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:07:13 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 11:09:14 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (size > 0)
	{
		while ((i < size - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

/*
#include <stdio.h>

int	main(void)
{
	char dst[] = "noor faronia";
	char src[] = "mahmoud";
	printf("dst before ft_strlcpy = %s \n ", dst);
	printf("src before ft_strlcpy = %s \n ", src);
	ft_strlcpy(dst, src, 5);
	printf("dst after ft_strlcpy = %s \n ", dst);
	printf("src after ft_strlcpy = %s \n ", src);
	return (0);
}*/
