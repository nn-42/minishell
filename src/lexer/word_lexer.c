/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:05 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/11 07:41:37 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sep(char c)
{
	return (c == ' ' || c == '|'
		|| c == '\t' || c == '\n'
		|| c == '<' || c == '>');
}

char	*plain(char *line, int *i)
{
	int		start;
	char	*part;

	start = *i;
	while (line[*i] && !sep(line[*i])
		&& line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	part = ft_substr(line, start, *i - start);
	return (part);
}

void	appennd_part(char **result, char *part)
{
	char	*temp;

	temp = ft_strjoin(*result, part);
	free(*result);
	free(part);
	if (!temp)
		return ;
	*result = temp;
}

int	word(char *line, int *i, t_token **tokens)
{
	char	*tokens_word;
	char	*part;

	tokens_word = ft_strdup("");
	if (!tokens_word)
		return (0);
	while (line[*i] && !sep(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (!quote(&part, line, i))
				return (free(tokens_word), 0);
		}
		else
		{
			part = plain(line, i);
			if (!part)
				return (free(tokens_word), 0);
		}
		appennd_part(&tokens_word, part);
	}
	add_token(tokens, TOKEN_WORD, tokens_word);
	free(tokens_word);
	return (1);
}
