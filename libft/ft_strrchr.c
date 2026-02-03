/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:18:33 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 11:41:24 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	char *s = "faronia";
	int a = 'a';
	int i = 'i';
	int x = 'x';
	printf("a in faronia : %s \n", ft_strrchr(s, a));
	printf("i in faronia : %s \n", ft_strrchr(s, i));
	printf("x in faronia : %s \n", ft_strrchr(s, x));
	return (0);
}*/
