/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:58:17 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/08 23:58:33 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(char *msg)
{
	fprintf(stderr, "Parser Error: %s\n", msg);
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

t_ast	*parser(t_token *tokens)
{
	t_parser	pars;
	t_ast		*tree;

	pars.current = tokens;
	pars.error = 0;
	tree = parse_pipe(&pars);
	if (!tree || pars.error)
		return (NULL);
	if (!pars.error && pars.current && pars.current->type != TOKEN_EOF)
	{
		parse_error("syntax error at end of input\n");
		free_ast(tree);
		return (NULL);
	}
	return (tree);
}
