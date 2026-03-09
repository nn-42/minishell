/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/09 06:47:34 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander_error(char *msg)
{
	fprintf(stderr, "Expander Error: %s\n", msg);
}

char	*expander_all(char *str, t_exec *env)
{
	char	*quotes;
	char	*var;

	quotes = expander_quotes(str);
	if (!quotes)
		return (NULL);
	var = expander_variables(quotes, env);
	free (quotes);
	if (!var)
		return (NULL);
	return (var);
}

int	expander_args(char **args, t_exec *env)
{
	int		i;
	char	*exp;

	i = 0;
	while (args && args[i])
	{
		exp = expander_all(args[i], env);
		if (!exp)
		{
			expander_error("failed to expand argument");
			while (args[i])
			{
				free(args[i]);
				args[i] = NULL;
				i++;
			}
			return (1);
		}
		free(args[i]);
		args[i] = exp;
		i++;
	}
	return (0);
}

int	expander_redirs(t_redir *redir, t_exec *env)
{
	char	*exp;

	while (redir)
	{
		exp = expander_all(redir->filename, env);
		if (!exp)
		{
			expander_error("failed to expand redir");
			while (redir)
			{
				free(redir->filename);
				redir->filename = NULL;
				redir = redir->next;
			}
			return (1);
		}
		free(redir->filename);
		redir->filename = exp;
		redir = redir->next;
	}
	return (0);
}

int	expander(t_ast *node, t_exec *env)
{
	if (!node)
		return (0);
	if (node->args && expander_args(node->args, env))
		return (1);
	if (node->redirs && expander_redirs(node->redirs, env))
		return (1);
	if (expander(node->left, env))
		return (1);
	if (expander(node->right, env))
		return (1);
	return (0);
}

/*
char	*expand_arg(char *arg, t_exec *exec)
{
	char	*tmp;
	char	*new;

	tmp = expander_quotes(arg);
	new = expander_variables(tmp, exec);
	free(tmp);
	return (new);
}

void	expand_command(t_ast *cmd, t_exec *exec)
{
	int		i;
	t_redir	*r;
	char	*new_file;
	char	*new_arg;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_arg = expand_arg(cmd->args[i], exec);
		free(cmd->args[i]);
		cmd->args[i] = new_arg;
		i++;
	}
	r = cmd->redirs;
	while (r)
	{
		new_file = expand_arg(r->filename, exec);
		free(r->filename);
		r->filename = new_file;
		r = r->next;
	}
}
*/