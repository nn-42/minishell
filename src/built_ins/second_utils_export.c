/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:07:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 05:25:34 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
