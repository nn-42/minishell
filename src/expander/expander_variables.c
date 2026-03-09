/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/09 06:42:22 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_exec *env, char *var_name)
{
	int		i;
	size_t	len;
	char	*s;

	if (!env || !env->envp || !var_name)
		return (NULL);
	i = 0;
	len = ft_strlen(var_name);
	while (env->envp[i])
	{
		s = env->envp[i];
		if (!ft_strncmp(s, var_name, len) && s[len] == '=')
			return (ft_strdup(s + len + 1));
		i++;
	}
	return (NULL);
}

char	*var(char *str, int *i, t_exec *env)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*new;

	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(env, var_name);
	if (!var_value)
		var_value = ft_strdup("");
	free(var_name);
	new = ft_strdup(var_value);
	free(var_value);
	if (!new)
		return (NULL);
	return (new);
}

char	*expander_variables(char *str, t_exec *env)
{
	int		i;
	char	*new_str;
	char	*expanded;
	char	*temp;

	i = 0;
	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			expanded = var(str, &i, env);
			if (!expanded)
				return (NULL);
			temp = ft_strjoin(new_str, expanded);
			free(new_str);
			free(expanded);
			if (!temp)
				return (NULL);
			new_str = temp;
		}
		else
			new_str = rest_char(new_str, str[i++]);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}
