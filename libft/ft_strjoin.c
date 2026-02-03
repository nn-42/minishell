/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:52:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/11 12:40:21 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	len(size_t	*len_s1, size_t	*len_s2, char const *s1, char const *s2)
{
	*len_s1 = ft_strlen(s1);
	*len_s2 = ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;

	len(&len_s1, &len_s2, s1, s2);
	ptr = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len_s2)
	{
		ptr[len_s1 + i] = s2[i];
		i++;
	}
	ptr[len_s1 + len_s2] = '\0';
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	char const *s1 = "noor";
	char const *s2 = " faronia";
	printf("s1 + s2 = %s \n", ft_strjoin(s1, s2));
	return (0);
}*/
