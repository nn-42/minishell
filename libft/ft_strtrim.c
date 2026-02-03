/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:04:11 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/30 11:30:32 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start;
	size_t	end;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (0);
	start = 0;
	while (s1[start] && inset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && inset(s1[end - 1], set))
		end--;
	ptr = malloc(sizeof(char) * (end - start + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1 + start, end - start + 1);
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	char const *s1 = "   noor faronia   ";
	char const *set = " ";
	printf("trim is : \"%s\" \n", ft_strtrim(s1, set));
	return (0);
}*/
