/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:41:37 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:05:04 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_envp_without_index(char **old_envp,
		int count, int skip_index)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != skip_index)
		{
			new_env[j] = old_envp[i];
			j++;
		}
		else
			free(old_envp[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	unset_env_var(char ***envp, char *name)
{
	int		index;
	int		count;
	char	**new_env;

	index = find_env_var(*envp, name);
	if (index == -1)
		return (0);
	count = count_env_vars(*envp);
	new_env = create_envp_without_index(*envp, count, index);
	if (!new_env)
		return (-1);
	free(*envp);
	*envp = new_env;
	return (0);
}

int	builtin_unset(char **args, t_exec *exec_ctx)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (unset_env_var(&exec_ctx->envp, args[i]) < 0)
		{
			error_msg("unset", args[i], "failed to remove");
			return (1);
		}
		i++;
	}
	return (0);
}
