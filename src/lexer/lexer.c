/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:05 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 01:13:12 by nfaronia         ###   ########.fr       */
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

void	word(char *line, int *i, t_token **tokens)
{
	int		start;
	char	*tokens_word;
	char	quote;

	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		start = *i;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		tokens_word = ft_substr(line, start, *i - start);
		if (line[*i] == quote)
			(*i)++;
	}
	else
	{
		start = *i;
		while (line[*i] && line[*i] != ' ' && line[*i] != '|'
			&& line[*i] != '<' && line[*i] != '>')
			(*i)++;
		tokens_word = ft_substr(line, start, *i - start);
	}
	add_token(tokens, TOKEN_WORD, tokens_word);
	free(tokens_word);
}

t_token	*lexer(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			operator(line, &i, &tokens);
		else
			word(line, &i, &tokens);
	}
	return (tokens);
}
