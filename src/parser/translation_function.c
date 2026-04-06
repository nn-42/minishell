/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:30:14 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/05 00:18:16 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir *copy_redirs(t_redir *redir)
{
    t_redir *new_list = NULL;
    t_redir *current = redir;
    t_redir *new_node;

    while (current)
    {
        new_node = malloc(sizeof(t_redir));
        if (!new_node)
            return (NULL);
        new_node->type = current->type;
        new_node->filename = ft_strdup(current->filename);
        new_node->next = new_list;
        new_list = new_node;
        current = current->next;
    }
    return (new_list);
}


t_cmd *create_cmd_from_ast(t_ast *node)
{
    t_cmd *cmd;
    int i, count;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);

    // انسخ الـ args
    count = 0;
    while (node->args && node->args[count])
        count++;
    cmd->args = malloc(sizeof(char *) * (count + 1));
    if (!cmd->args)
        return (NULL);
    for (i = 0; i < count; i++)
        cmd->args[i] = ft_strdup(node->args[i]);
    cmd->args[count] = NULL;

    // انسخ الـ redirs (ممكن تعمل دالة copy_redirs)
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
