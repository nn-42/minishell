/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:43:04 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:50:29 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir(t_ast *node, t_parser	*pars)
{
	t_redir			*redir;
	t_token_type	type;

	type = pars->current->type;
	next_token(pars);
	if (!pars->current || pars->current->type == TOKEN_EOF)
	{
		parse_error("syntax error near unexpected token `newline'");
		pars->error = 1;
		return ;
	}
	if (pars->current->type != TOKEN_WORD)
	{
		if (pars->current->type == TOKEN_PIPE)
			parse_error("syntax error near unexpected token `|'");
		else if (pars->current->type == TOKEN_REDIR_APPEND)
			parse_error("syntax error near unexpected token `>>'");
		else if (pars->current->type == TOKEN_REDIR_OUT)
			parse_error("syntax error near unexpected token `>'");
		else if (pars->current->type == TOKEN_REDIR_IN)
			parse_error("syntax error near unexpected token `<'");
		else
			parse_error("syntax error near unexpected token");
		pars->error = 1;
		return ;
	}
	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		pars->error = 1;
		return ;
	}
	redir->type = type;
	redir->file = ft_strdup(pars->current->value);
	if (!redir->file)
	{
		free(redir);
		pars->error = 1;
		return ;
	}
	redir->quoted = pars->current->quoted;
	redir->ambiguous = 0;
	redir->heredoc_pipe = -1;
	redir->next = node->redirs;
	node->redirs = redir;
	next_token(pars);
}

void	free_redir(t_redir *redir)
{
	t_redir	*f;

	while (redir)
	{
		f = redir;
		redir = redir->next;
		if (f->file)
			free(f->file);
		free(f);
	}
}

void	expand_args_array(char ***arr, char *str)
{
	int		len;
	char	**new_arr;
	int		i;

	len = 0;
	while (*arr && (*arr)[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return ;
	i = 0;
	while (i < len)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	new_arr[len] = str;
	new_arr[len + 1] = NULL;
	free(*arr);
	*arr = new_arr;
}

void	add_arg(t_ast *node, t_parser *pars)
{
	char	*s;
	int		len;
	int		*new_quoted;
	int		i;

	s = ft_strdup(pars->current->value);
	if (!s)
	{
		pars->error = 1;
		return ;
	}
	len = 0;
	while (node->args && node->args[len])
		len++;
	new_quoted = malloc(sizeof(int) * (len + 2));
	if (!new_quoted)
	{
		free(s);
		pars->error = 1;
		return ;
	}
	i = 0;
	while (i < len)
	{
		if (node->args_quoted)
			new_quoted[i] = node->args_quoted[i];
		else
			new_quoted[i] = NO_QUOTE;
		i++;
	}
	new_quoted[len] = pars->current->quoted;
	new_quoted[len + 1] = 0;
	free(node->args_quoted);
	node->args_quoted = new_quoted;
	expand_args_array(&node->args, s);
	next_token(pars);
}

void	free_arg(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
