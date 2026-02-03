/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:20:21 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 11:53:47 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] == s2[i]) && s1[i] != '\0')
		i++;
	if (s1[i] != s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s1 = "noor";
	char *s2 = "noo or";
	printf("indix 2 %d \n", ft_strncmp(s1, s2, 2));
	printf("indix 3 %d \n", ft_strncmp(s1, s2, 3));
	printf("indix 5 %d \n", ft_strncmp(s1, s2, 5));
	printf("indix 4 %d \n", ft_strncmp(s1, s2, 4));
	return (0);
}*/
