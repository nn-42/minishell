/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:07:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/09 03:04:53 by nfaronia         ###   ########.fr       */
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

int	parse_export_arg(char *arg, char **name, char **value)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (!equals)
		return (0);
	*name = ft_substr(arg, 0, equals - arg);
	*value = ft_strdup(equals + 1);
	if (!*name || !*value)
	{
		free(*name);
		free(*value);
		return (0);
	}
	return (1);
}

//////////////////////
int is_valid_identifier(char *name)
{
    int i = 0;

    if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
        return 0;
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return 0;
        i++;
    }
    return 1;
}
int export_arg(char *arg, t_exec *exec_ctx)
{
    char *name;
    char *value;

    if (parse_export_arg(arg, &name, &value))
    {
        if (!is_valid_identifier(name))
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
            free(name);
            free(value);
            return 1;
        }
        if (set_env_var(&exec_ctx->envp, name, value) < 0)
        {
            fprintf(stderr, "export: failed to set %s\n", name);
            free(name);
            free(value);
            return 1;
        }
        free(name);
        free(value);
    }
    else
    {
        if (!is_valid_identifier(arg))
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
            return 1;
        }
        if (set_env_var(&exec_ctx->envp, arg, "") < 0)
        {
            fprintf(stderr, "export: failed to set %s\n", arg);
            return 1;
        }
    }
    return 0;
}

//////////////////////
/*
int	export_arg(char *arg, t_exec *exec_ctx)
{
	char	*name;
	char	*value;

	if (parse_export_arg(arg, &name, &value))
	{
		if (set_env_var(&exec_ctx->envp, name, value) < 0)
		{
			printf("export: failed to set %s\n", name);
			free(name);
			free(value);
			return (1);
		}
		free(name);
		free(value);
	}
	else
	{
		printf("export: `%s': not a valid identifier\n", arg);
	}
	return (0);
}*/

int	builtin_export(char **args, t_exec *exec_ctx)
{
	int		i;

	if (!args[1])
	{
		print_export_format(exec_ctx->envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (export_arg(args[i], exec_ctx))
			return (1);
		i++;
	}
	return (0);
}
