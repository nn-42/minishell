/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:07:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/11 02:59:15 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_var(char ***envp, char *name, char *value)
{
	int		index;
	char	*new_var;
	char	*temp;

	index = find_env_var(*envp, name);
	if (index == -1)
		return (0);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (-1);
	new_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_var)
		return (-1);
	free((*envp)[index]);
	(*envp)[index] = new_var;
	return (1);
}

char	*build_var(char *name, char *value)
{
	char	*new_var;
	char	*temp;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	new_var = ft_strjoin(temp, value);
	free(temp);
	return (new_var);
}

int	add_env_var(char ***envp, char *name, char *value)
{
	char	**new_env;
	char	*new_var;
	int		count;
	int		i;

	new_var = build_var(name, value);
	if (!new_var)
		return (-1);
	count = count_env_vars(*envp);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (free(new_var), -1);
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (1);
}

int	set_env_var(char ***envp, char *name, char *value)
{
	int	result;

	result = update_env_var(envp, name, value);
	if (result == 1)
		return (0);
	if (result == -1)
		return (-1);
	result = add_env_var(envp, name, value);
	if (result == -1)
		return (-1);
	return (0);
}
