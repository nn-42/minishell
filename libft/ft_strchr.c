/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:16:27 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 11:35:22 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	char *s = "faronia";
	int o = 'o';
	int i = 'i';
	int x = 'x';
	printf("o in faronia : %s \n", ft_strchr(s, o));
	printf("i in faronia : %s \n", ft_strchr(s, i));
	printf("x in faronia : %s \n", ft_strchr(s, x));
	return (0);
}*/
