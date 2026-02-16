/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:05 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 18:17:28 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hori(char *line, int *i, t_token **tokens)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(tokens, TOKEN_HEREDOC, "<<");
		(*i) += 2;
	}
	else if (line[*i] == '<')
	{
		add_token(tokens, TOKEN_REDIR_IN, "<");
		(*i)++;
	}
}

void	aort(char *line, int *i, t_token **tokens)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(tokens, TOKEN_APPEND, ">>");
		(*i) += 2;
	}
	else if (line[*i] == '>')
	{
		add_token(tokens, TOKEN_REDIR_OUT, ">");
		(*i)++;
	}
}

void	operator(char *line, int *i, t_token **tokens)
{
	if (line[*i] == '|')
	{
		add_token(tokens, TOKEN_PIPE, "|");
		(*i)++;
	}
	else if (line[*i] == '<')
		hori(line, i, tokens);
	else if (line[*i] == '>')
		aort(line, i, tokens);
}

int	word(char *line, int *i, t_token **tokens)
{
	int		start;
	char	*tokens_word;

	if (line[*i] == '\'' || line[*i] == '"')
	{
		if (!quote(&tokens_word, line, i))
			return (0);
	}
	else
	{
		start = *i;
		while (line[*i] && line[*i] != ' ' && line[*i] != '|'
			&& line[*i] != '\t' && line[*i] != '<' && line[*i] != '>'
			&& line[*i] != '\'' && line[*i] != '"')
			(*i)++;
		tokens_word = ft_substr(line, start, *i - start);
		if (!tokens_word)
			return (0);
	}
	add_token(tokens, TOKEN_WORD, tokens_word);
	free(tokens_word);
	return (1);
}

t_token	*lexer(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			operator(line, &i, &tokens);
		else
		{
			if (!word(line, &i, &tokens))
			{
				free_tokens(tokens);
				return (NULL);
			}
		}
	}
	add_token(&tokens, TOKEN_EOF, NULL);
	return (tokens);
}
