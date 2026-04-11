/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:07:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/11 03:12:34 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!name || (!ft_isalpha(name[i]) && name[i] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_export(char *name, char *value, char *arg, t_exec *exec_ctx)
{
	if (!is_valid_identifier(name))
	{
		error_msg("export", arg, "not a valid identifier");
		free (name);
		free(value);
		return (1);
	}
	if (set_env_var(&exec_ctx->envp, name, value) < 0)
	{
		error_msg("export", name, "failed to set");
		free (name);
		free(value);
		return (1);
	}
	free (name);
	free(value);
	return (0);
}

int	export_arg(char *arg, t_exec *exec_ctx)
{
	char	*name;
	char	*value;

	if (parse_export_arg(arg, &name, &value))
		return (handle_export(name, value, arg, exec_ctx));
	if (!is_valid_identifier(arg))
	{
		error_msg("export", arg, "not a valid identifier");
		return (1);
	}
	if (set_env_var(&exec_ctx->envp, arg, "") < 0)
	{
		error_msg("export", arg, "failed to set");
		return (1);
	}
	return (0);
}

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
