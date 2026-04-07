/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_utils_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:07:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/07 07:10:58 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_format(char **envp)
{
	int		i;
	char	*equals;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i])
	{
		equals = ft_strchr(envp[i], '=');
		if (equals)
		{
			name = ft_substr(envp[i], 0, equals - envp[i]);
			value = equals + 1;
			printf("declare -x %s=\"%s\"\n", name, value);
			free(name);
		}
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**dup_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = count_env_vars(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

void	free_env(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	find_env_var(char **envp, char *name)
{
	int		i;
	int		name_len;

	if (!envp || !name)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
