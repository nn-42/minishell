/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_utils_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:03:35 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 07:27:28 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirections, exec_ctx) < 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	status = execute_builtin(cmd->args, exec_ctx);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	exec_ctx->last_exit = status;
	return (status);
}

int	execute_external_cmd(t_cmd *cmd, t_exec *exec_ctx, char *path, pid_t pid)
{
	int		status;

	if (pid == 0)
	{
		if (apply_redirections(cmd->redirections, exec_ctx) < 0)
			exit(1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->args, exec_ctx->envp);
		perror("minishell");
		free(path);
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exec_ctx->last_exit = WEXITSTATUS(status);
		free(path);
		return (exec_ctx->last_exit);
	}
	perror("fork");
	free(path);
	return (1);
}

int	execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	pid_t	pid;
	char	*path;
	int		result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin_cmd(cmd, exec_ctx));
	path = resolve_cmd_path(cmd->args[0], exec_ctx);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		exec_ctx->last_exit = 127;
		return (127);
	}
	pid = fork();
	result = execute_external_cmd(cmd, exec_ctx, path, pid);
	return (result);
}

int	count_commands(t_cmd *commands)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = commands;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
