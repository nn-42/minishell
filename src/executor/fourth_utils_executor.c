/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fourth_utils_executor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:03:35 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 07:57:11 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe_redirections(int **pipes, int cmd_index, int num_commands)
{
	if (cmd_index == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
	}
	else if (cmd_index == num_commands - 1)
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	else
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
}

void	setup_pipeline_and_redirections(t_cmd *cmd, t_exec *exec_ctx,
			t_pipe_ctx *pctx)
{
	if (pctx->pipes)
		setup_pipe_redirections(pctx->pipes, pctx->index, pctx->num);
	if (apply_redirections(cmd->redirections, exec_ctx) < 0)
		exit(1);
	if (pctx->pipes)
		close_pipes(pctx->pipes, pctx->num - 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	execute_pipeline_command(t_cmd *cmd, t_exec *exec_ctx, t_pipe_ctx *pctx)
{
	char	*path;

	setup_pipeline_and_redirections(cmd, exec_ctx, pctx);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd->args, exec_ctx));
	path = resolve_cmd_path(cmd->args[0], exec_ctx);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(path, cmd->args, exec_ctx->envp);
	perror("minishell");
	exit(127);
}
