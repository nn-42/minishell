/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 13:52:17 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/07 13:55:52 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*cmd_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->redirs = NULL;
	return (node);
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

void	next_token(t_parser *pars)
{
	if (pars->current)
		pars->current = pars->current->next;
}

t_ast	*parse_cmd(t_parser *pars)
{
	t_ast	*node;

	node = cmd_node();
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
