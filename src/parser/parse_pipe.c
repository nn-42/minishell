/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:47:24 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/07 13:49:42 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->left = left;
	node->right = right;
	node->args = NULL;
	node->redirs = NULL;
	return (node);
}

bool	match_token(t_parser *pars, t_token_type type)
{
	if (pars->current && pars->current->type == type)
	{
		next_token(pars);
		return (true);
	}
	return (false);
}

t_ast	*parse_pipe(t_parser *pars)
{
	t_ast		*left;
	t_ast		*right;

	left = parse_cmd(pars);
	if (!left)
		return (NULL);
	while (match_token(pars, TOKEN_PIPE))
	{
		if (!pars->current || pars->current->type == TOKEN_PIPE)
		{
			parse_error("syntax error near pipe");
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
