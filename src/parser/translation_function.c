/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:30:14 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:49:18 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*copy_redirs(t_redir *redir)
{
	t_redir	*new_list;
	t_redir	*current;
	t_redir	*new_node;

	new_list = NULL;
	current = redir;
	while (current)
	{
		new_node = malloc(sizeof(t_redir));
		if (!new_node)
		{
			free_redir(new_list);
			return (NULL);
		}
		new_node->type = current->type;
		new_node->file = ft_strdup(current->file);
		new_node->quoted = current->quoted;
		new_node->ambiguous = current->ambiguous;
		new_node->heredoc_pipe = current->heredoc_pipe;
		new_node->next = new_list;
		new_list = new_node;
		current = current->next;
	}
	return (new_list);
}

t_cmd	*create_cmd_from_ast(t_ast *node)
{
	t_cmd	*cmd;
	int		i;
	int		count;

	count = 0;
	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (node->args && node->args[count])
		count++;
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	while (i < count)
	{
		cmd->args[i] = ft_strdup(node->args[i]);
		i++;
	}
	cmd->args[count] = NULL;
	cmd->redirections = copy_redirs(node->redirs);
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*ast_to_cmd_list(t_ast *node)
{
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*last;

	if (!node)
		return (NULL);
	if (node->type == NODE_CMD)
		return (create_cmd_from_ast(node));
	else if (node->type == NODE_PIPE)
	{
		left = ast_to_cmd_list(node->left);
		right = ast_to_cmd_list(node->right);
		last = left;
		while (last && last->next)
			last = last->next;
		if (last)
			last->next = right;
		else
			left = right;
		return (left);
	}
	return (NULL);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->redirections)
			free_redir(cmd->redirections);
		free(cmd);
		cmd = tmp;
	}
}
