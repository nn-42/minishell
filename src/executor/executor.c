/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:03:35 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 10:48:30 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipes(t_pipe_ctx *pctx)
{
	int		i;

	pctx->pipes = malloc(sizeof(int *) * (pctx->num - 1));
	if (!pctx->pipes)
		return (-1);
	i = 0;
	while (i < pctx->num - 1)
	{
		pctx->pipes[i] = malloc(sizeof(int) * 2);
		if (!(pctx->pipes)[i] || pipe(pctx->pipes[i]) < 0)
		{
			while (i-- > 0)
				free(pctx->pipes[i]);
			free(pctx->pipes);
			perror("pipe");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	spawn_children(t_cmd *commands, t_exec *exec_ctx,
			t_pipe_ctx *pctx, pid_t *pids)
{
	int		i;
	t_cmd	*current;

	current = commands;
	i = 0;
	while (i < pctx->num)
	{
		pctx->index = i;
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork");
			return ;
		}
		if (pids[i] == 0)
			execute_pipeline_command(current, exec_ctx, pctx);
		current = current->next;
		i++;
	}
}

int	execute_pipeline(t_cmd *commands, t_exec *exec_ctx)
{
	t_pipe_ctx	pctx;
	pid_t		*pids;
	int			i;
	int			status;

	pctx.num = count_commands(commands);
	if (pctx.num == 1)
		return (execute_simple_cmd(commands, exec_ctx));
	if (init_pipes(&pctx) < 0)
		return (1);
	pids = malloc(sizeof(pid_t) * pctx.num);
	spawn_children(commands, exec_ctx, &pctx, pids);
	close_pipes(pctx.pipes, pctx.num - 1);
	i = -1;
	while (++i < pctx.num)
		waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		exec_ctx->last_exit = WEXITSTATUS(status);
	i = -1;
	while (++i < pctx.num - 1)
		free(pctx.pipes[i]);
	free(pctx.pipes);
	free(pids);
	return (exec_ctx->last_exit);
}

void	update_exit_status(t_exec *exec_ctx, int status)
{
	exec_ctx->last_exit = status;
}
