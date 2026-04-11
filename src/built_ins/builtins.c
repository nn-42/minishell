/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:51:06 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/10 23:37:18 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **args, t_exec *exec_ctx)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, exec_ctx));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, exec_ctx));
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, exec_ctx));
	if (ft_strcmp(args[0], "echo") == 0)
		return (built_echo(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, exec_ctx));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (built_pwd());
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, exec_ctx));
	return (0);
}

void	cleanup_shell(t_exec *exec_ctx)
{
	rl_clear_history();
	free_history();
	if (exec_ctx && exec_ctx->envp)
		free_env(exec_ctx->envp);
}
