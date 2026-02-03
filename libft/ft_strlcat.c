/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:09:59 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 11:19:12 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	j = 0;
	n = 0;
	while (src[j] != '\0')
		j++;
	while (dst[i] != '\0')
		i++;
	if (size <= i)
		return (size + j);
	while ((i + n < size - 1) && src[n] != '\0')
	{
		dst[i + n] = src[n];
		n++;
	}
	if (size > 0)
		dst[i + n] = '\0';
	return (j + i);
}

/*
#include <stdio.h>

int	main(void)
{
	char dst[20] = "noor faronia";
	char src[] = "maho";
	printf("dst before ft_strlcat : %s \n ", dst);
	printf("src before ft_strlcat : %s \n ", src);
	ft_strlcat(dst, src, 20);
	printf("dst after ft_strlcat : %s \n ", dst);
	printf("src after ft_strlcat : %s \n ", src);
	return (0);
}*/
