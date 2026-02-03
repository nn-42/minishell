/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:36:07 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/30 11:36:36 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;
	size_t			len;

	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (i < len)
	{
		ptr[i] = (*f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
#include <stdio.h>

char	pls(unsigned int i, char c)
{
	//(void)i;
	c = c + 1;
	return (c);
}

int	main(void)
{
	char *str = "hello!";
	char *result = ft_strmapi(str, pls);

	if (result)
	{
		printf("Original: %s\n", str);
		printf("Modified: %s\n", result);
		free(result);
	}
	else
		printf("Memory allocation failed.\n");

	return (0);
}*/
