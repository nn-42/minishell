/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:58:17 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/25 15:44:09 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_pipe(t_parser *pars)
{
	t_ast		*left;
	t_ast		*right;

	left = parse_cmd(pars);
	if (!left)
		return (NULL);
	while (is_match(pars, TOKEN_PIPE))
	{
		if (!pars->current || pars->current->type == TOKEN_PIPE)
		{
			free_ast(left);
			return (NULL);
		}
		right = parse_cmd(pars);
		if (!right)
		{
			free_ast(left);
			return (NULL);
		}
		left = pipe_node(left, right);
	}
	return (left);
}

bool	pars_type(t_parser *pars)
{
	if (pars->current->type == TOKEN_REDIR_IN
		|| pars->current->type == TOKEN_REDIR_OUT
		|| pars->current->type == TOKEN_APPEND
		|| pars->current->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

t_ast	*parse_cmd(t_parser *pars)
{
	t_ast	*node;

	node = creat_node();
	while (pars->current && pars->current->type != TOKEN_PIPE
		&& pars->current->type != TOKEN_EOF && !pars->error)
	{
		if (pars->current->type == TOKEN_WORD)
			add_arg(node, pars);
		else if (pars_type(pars))
			add_redir(node, pars);
		else
			break ;
	}
	if (pars->error)
	{
		free_ast(node);
		return (NULL);
	}
	if (!node->args && !node->redirs)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast	*parser(t_token *tokens)
{
	t_parser	pars;
	t_ast		*tree;

	pars.current = tokens;
	pars.error = 0;
	tree = parse_pipe(&pars);
	if (!tree)
		return (NULL);
	if (pars.error)
		return (NULL);
	if (!pars.error && pars.current && pars.current->type != TOKEN_EOF)
	{
		printf("syntax error\n");
		free_ast(tree);
		return (NULL);
	}
	return (tree);
}
