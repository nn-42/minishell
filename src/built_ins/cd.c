/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:23:41 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 16:55:06 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int	builtin_cd(char **args, t_exec *exec_ctx)
{
	char	*path;
	char	*home;
	char	*old_pwd;
	char	*new_pwd;
	int		index;

	old_pwd = getcwd(NULL, 0);
	if (!args[1])
	{
		index = find_env_var(exec_ctx->envp, "HOME");
		if (index == -1)
		{
			printf("cd: HOME not set\n");
			free(old_pwd);
			return (1);
		}
		home = ft_strchr(exec_ctx->envp[index], '=');
		if (!home)
		{
			free(old_pwd);
			return (1);
		}
		path = home + 1;
	}
	else if (args[2])
	{
		printf("cd: too many arguments\n");
		free(old_pwd);
		return (1);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_var(&exec_ctx->envp, "PWD", new_pwd);
		free(new_pwd);
	}
	if (old_pwd)
	{
		set_env_var(&exec_ctx->envp, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	return (0);
}
/*
char	*get_home(t_exec *exec_ctx, char *old_pwd)
{
	char	*home;
	int		i;

	i = find_env_var(exec_ctx->envp, "HOME");
	if (i == -1)
	{
		printf("cd: HOME not set\n");
		free(old_pwd);
		return (NULL);
	}
	home = ft_strchr(exec_ctx->envp[i], '=');
	if (!home)
	{
		free(old_pwd);
		return (NULL);
	}
	return (ft_strdup(home + 1));
}

char	*get_path(char **args, t_exec *exec_ctx, char *old_pwd)
{
	if (!args[1])
		return (get_home(exec_ctx, old_pwd));
	if (args[2])
	{
		printf("cd: too many arguments\n");
		free(old_pwd);
		return (NULL);
	}
	return (args[1]);
}

int	set_env(char *old_pwd, t_exec *exec_ctx)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_var(&exec_ctx->envp, "PWD", new_pwd);
		free(new_pwd);
	}
	if (old_pwd)
	{
		set_env_var(&exec_ctx->envp, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	return (0);
}

int	builtin_cd(char **args, t_exec *exec_ctx)
{
	char	*path;
	char	*old_pwd;
	int		new_env;
	int		need_free;

	old_pwd = getcwd(NULL, 0);
	path = get_path(args, exec_ctx, old_pwd);
	need_free = 0;
	if (!path)
		return (1);
	if (!args[1])
		need_free = 1;
	if (chdir(path) != 0)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		free(old_pwd);
		if (need_free)
			free(path);
		return (1);
	}
	new_env = set_env(old_pwd, exec_ctx);
	if (need_free)
		free(path);
	return (new_env);
}*/
