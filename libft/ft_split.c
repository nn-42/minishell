/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:25:45 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/30 11:25:47 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	nword;

	i = 0;
	nword = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			nword++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (nword);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*ptr;
	int		i;

	ptr = malloc(sizeof(char) * (end - start + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (start < end)
	{
		ptr[i] = str[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	*ft_free(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

static char	**fill_arr(char const *s, char c, size_t i, size_t j)
{
	char	**arr;
	int		start;

	arr = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!arr)
		return (NULL);
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start == -1)
			start = (int)i;
		else if ((s[i] == c || i == ft_strlen(s)) && start != -1)
		{
			arr[j] = fill_word(s, start, i);
			if (!(arr[j]))
				return (ft_free(arr, j - 1));
			start = -1;
			j++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	arr = fill_arr(s, c, i, j);
	return (arr);
}

/*
#include <stdio.h>

int	main(void)
{
	char **arr = ft_split("my  name is     noor", ' ');
	int i = 0;
	while (arr[i])
	{
		printf("arr[%d] = \"%s\"\n", i, arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}*/
