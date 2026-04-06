/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 02:03:16 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 14:17:26 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include "minishell.h"

typedef struct s_redir	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char	**envp;
	int		last_exit;
}	t_exec;

typedef struct s_pipe_ctx
{
	int	**pipes;
	int	index;
	int	num;
}	t_pipe_ctx;

// executor.c
int		init_pipes(t_pipe_ctx *pctx);
void	spawn_children(t_cmd *commands, t_exec *exec_ctx,
			t_pipe_ctx *pctx, pid_t *pids);
int		execute_pipeline(t_cmd *commands, t_exec *exec_ctx);
void	update_exit_status(t_exec *exec_ctx, int status);

// first_utils_executor.c
int		is_executable(char *path);
char	*search_in_path(char **paths, char *command);
char	*find_command_in_path(char *command, t_exec *exec_ctx);
char	*resolve_cmd_path(char *command, t_exec *exec_ctx);
int		handle_input_redir(char *filename);

// second_utils_executor.c
int		handle_output_redir(char *filename);
int		handle_append_redir(char *filename);
void	read_loop(char *delimiter, int fd, t_exec *exec_ctx);
int		handle_heredoc(char *delimiter, t_exec *exec_ctx);
int		apply_redirections(t_redir *redirections, t_exec *exec_ctx);

// third_utils_executor.c
int		execute_builtin_cmd(t_cmd *cmd, t_exec *exec_ctx);
int		execute_external_cmd(t_cmd *cmd, t_exec *exec_ctx,
			char *path, pid_t pid);
int		execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx);
int		count_commands(t_cmd *commands);
void	close_pipes(int **pipes, int num_pipes);

// fourth_utils_executor.c
void	setup_pipe_redirections(int **pipes, int cmd_index, int num_commands);
void	setup_pipeline_and_redirections(t_cmd *cmd, t_exec *exec_ctx,
			t_pipe_ctx *pctx);
void	execute_pipeline_command(t_cmd *cmd, t_exec *exec_ctx,
			t_pipe_ctx *pctx);

#endif