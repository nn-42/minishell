/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnasered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:37:49 by nnasered          #+#    #+#             */
/*   Updated: 2025/10/23 12:22:58 by nnasered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*ft_gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_gnl_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_gnl_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_gnl_strdup(s2));
	if (!s2)
		return (ft_gnl_strdup(s1));
	result = malloc(ft_gnl_strlen(s1) + ft_gnl_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

void	copy_line_content(char *dest, const char **src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = (*src)[i];
		i++;
	}
	dest[i] = '\0';
}
