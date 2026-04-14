/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:07:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:16:24 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
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

static int	parse_export_arg(char *arg, char **name, char **value)
{
	char	*equals;
	int		name_len;

	equals = ft_strchr(arg, '=');
	if (!equals)
	{
		*name = ft_strdup(arg);
		*value = NULL;
		if (*name)
			return (0);
		else
			return (-1);
	}
	name_len = equals - arg;
	*name = ft_substr(arg, 0, name_len);
	*value = expander_quotes(equals + 1);
	if (!*name || !*value)
	{
		free(*name);
		free(*value);
		return (0);
	}
	return (1);
}

static int	parse_and_validate_export_arg(char *arg, char **name,
		char **value, int *parse_result)
{
	*parse_result = parse_export_arg(arg, name, value);
	if (*parse_result == -1)
		return (1);
	if (!is_valid_identifier(*name))
	{
		error_msg("export", arg, "not a valid identifier");
		free(*name);
		free(*value);
		return (1);
	}
	return (0);
}

static int	handle_export_arg(char *arg, t_exec *exec_ctx)
{
	char	*name;
	char	*value;
	int		parse_result;
	int		ret;

	name = NULL;
	value = NULL;
	ret = 0;
	if (parse_and_validate_export_arg(arg, &name, &value, &parse_result) != 0)
		return (1);
	if (parse_result == 1)
	{
		if (set_env_var(&exec_ctx->envp, name, value) < 0)
		{
			error_msg("export", name, "failed to set");
			ret = 1;
		}
		free(name);
		free(value);
	}
	else
		free(name);
	return (ret);
}

int	builtin_export(char **args, t_exec *exec_ctx)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_export_format(exec_ctx->envp);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(args[i], exec_ctx))
			ret = 1;
		i++;
	}
	return (ret);
}
