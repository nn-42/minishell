/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 12:49:05 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/14 14:27:26 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_token(const char *value, t_token_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = strdup(value);
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

static void	add_token(t_token **list, t_token *tok)
{
	t_token	*tmp;

	if (!*list)
		*list = tok;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tok;
	}
}

static bool	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '|'
		|| c == '<' || c == '>');
}

t_token	*lexer(const char *line)
{
	t_token	*tokens;
	int		start;
	char	*word;
	int		i;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (isspace(line[i]))
		{
			i++;
			continue ;
		}
		if (line[i] == '|')
		{
			add_token(&tokens, new_token("|", PIPE));
			i++;
		}
		else if (line[i] == '<')
		{
			add_token(&tokens, new_token("<", REDIR_IN));
			i++;
		}
		else if (line[i] == '>')
		{
			add_token(&tokens, new_token(">", REDIR_OUT));
			i++;
		}
		else
		{
			start = i;
			while (line[i] && !is_delimiter(line[i]))
				i++;
			word = strndup(line + start, i - start);
			add_token(&tokens, new_token(word, WORD));
			free(word);
		}
	}
	return (tokens);
}

void	print_tokens(t_token *tokens)
{
	const char		*name;

	while (tokens)
	{
		if (tokens->type == WORD)
			name = "WORD";
		else if (tokens->type == PIPE)
			name = "PIPE";
		else if (tokens->type == REDIR_IN)
			name = "REDIR_IN";
		else
			name = "REDIR_OUT";
		printf("[%s:%s] ", name, tokens->value);
		tokens = tokens->next;
	}
	printf("\n");
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
