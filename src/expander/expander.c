/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:43:37 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander_error(char *msg)
{
	error_msg("Expander", NULL, msg);
}

int	expander(t_ast *node, t_exec *env)
{
	if (!node)
		return (0);
	if (node->args && expander_args(&node->args, node->args_quoted, env))
		return (1);
	if (node->redirs && expander_redirs(node->redirs, env))
		return (1);
	if (expander(node->left, env))
		return (1);
	if (expander(node->right, env))
		return (1);
	return (0);
}
