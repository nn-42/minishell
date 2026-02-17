/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:04:14 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 20:44:27 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_null_lexer(char *value, t_token	*token)
{
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
}

int	add_token(t_token	**tokens, t_token_type type, char *value)
{
	t_token	*token;
	t_token	*new_token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = type;
	is_null_lexer(value, token);
	if (value && !token->value)
	{
		free(token);
		return (0);
	}
	token->next = NULL;
	if (!*tokens)
		*tokens = token;
	else
	{
		new_token = *tokens;
		while (new_token->next)
			new_token = new_token->next;
		new_token->next = token;
	}
	return (1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

int	quote(char **tokens_word, char *line, int *i)
{
	int		start;
	char	quote;

	quote = line[*i];
	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		printf("syntax error: unclosed quote");
		*tokens_word = NULL;
		return (0);
	}
	(*i)++;
	*tokens_word = ft_substr(line, start, *i - start);
	if (!*tokens_word)
	{
		printf("malloc error\n");
		return (0);
	}
	return (1);
}
