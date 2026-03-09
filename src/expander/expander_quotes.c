/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/09 06:31:07 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quote(char **new_str, char *str, int *i)
{
	int		start;
	char	*new;
	char	*temp;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (!str[*i])
	{
		expander_error("unclosed single quote");
		return ;
	}
	new = ft_substr(str, start, *i - start);
	if (!new)
		return ;
	(*i)++;
	temp = ft_strjoin(*new_str, new);
	if (!temp)
	{
		free(new);
		return ;
	}
	free(*new_str);
	*new_str = temp;
	free(new);
}

void	double_quote(char **new_str, char *str, int *i)
{
	int		start;
	char	*new;
	char	*temp;

	start = ++(*i);
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (!str[*i])
	{
		expander_error("unclosed double quote");
		return ;
	}
	new = ft_substr(str, start, *i - start);
	if (!new)
		return ;
	(*i)++;
	temp = ft_strjoin(*new_str, new);
	if (!temp)
	{
		free(new);
		return ;
	}
	free(*new_str);
	*new_str = temp;
	free(new);
}

char	*rest_char(char *new_str, char c)
{
	char	*anther_char;
	char	*temp;

	anther_char = malloc(2);
	if (!anther_char)
	{
		free(new_str);
		return (NULL);
	}
	anther_char[0] = c;
	anther_char[1] = '\0';
	temp = ft_strjoin(new_str, anther_char);
	free(new_str);
	free(anther_char);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*expander_quotes(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	if (!new_str)
	{
		expander_error("malloc error");
		return (NULL);
	}
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote(&new_str, str, &i);
		else if (str[i] == '"')
			double_quote(&new_str, str, &i);
		else
		{
			new_str = rest_char(new_str, str[i++]);
			if (!new_str)
				return (NULL);
		}
	}
	return (new_str);
}
