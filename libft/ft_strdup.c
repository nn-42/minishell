/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:02:51 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 13:05:32 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	const char *original = "Hello, World!";
	char *copy;

	copy = ft_strdup(original);
	if (!copy)
		return (1);

	printf("copy : %s\n", copy);

	free(copy);
	return (0);
}*/
