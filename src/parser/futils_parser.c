/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futils_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:57:47 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/25 15:25:57 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_match(t_parser *pars, t_token_type type)
{
	if (pars->current && pars->current->type == type)
	{
		adv(pars);
		return (1);
	}
	return (0);
}

void	adv(t_parser *pars)
{
	if (pars->current)
		pars->current = pars->current->next;
}

t_ast	*creat_node(void)
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

t_ast	*pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NUDE_PIPE;
	node->left = left;
	node->right = right;
	node->args = NULL;
	node->redirs = NULL;
	return (node);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->args)
		free_arg(node->args);
	if (node->redirs)
		free_redir(node->redirs);
	free(node);
}
