/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnasered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:23:17 by nnasered          #+#    #+#             */
/*   Updated: 2025/08/24 12:00:03 by nnasered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*location;

	ch = (char)c;
	location = NULL;
	while (*s)
	{
		if (*s == ch)
			location = (char *)s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (location);
}
