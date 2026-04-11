#include "minishell.h"

int	is_executable(char *path)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*find_command_in_path(char *command, t_exec *exec_ctx)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;
	int		index;

	index = find_env_var(exec_ctx->envp, "PATH");
	if (index == -1)
		return (NULL);
	path_env = ft_strchr(exec_ctx->envp[index], '=');
	if (!path_env)
		return (NULL);
	path_env++;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (is_executable(full_path))
		{
			i = 0;
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}

char	*resolve_cmd_path(char *command, t_exec *exec_ctx)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (find_command_in_path(command, exec_ctx));
}

int	handle_input_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_output_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_append_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int read_heredoc_lines(int write_fd, t_redir *redir, t_exec *exec_ctx)
{
	char *line;
	char *expanded_delim;
	char *expanded_line;
	
	if (redir->quoted)
		expanded_delim = ft_strdup(redir->filename);
	else
		expanded_delim = expander_variables(redir->filename, exec_ctx);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (redir->quoted)
			expanded_line = ft_strdup(line);
		else
			expanded_line = expander_variables(line, exec_ctx);
		if (ft_strcmp(expanded_line, expanded_delim) == 0)
		{
			free(line);
			free(expanded_line);
			break ;
		}
		write(write_fd, expanded_line, ft_strlen(expanded_line));
		write(write_fd, "\n", 1);
		free(line);
		free(expanded_line);
	}
	free(expanded_delim);
	return (0);
}

int	process_heredocs(t_cmd *cmd, t_exec *exec_ctx)
{
	t_redir	*current;
	int		pipe_fds[2];
	pid_t	pid;
	int		status;
	struct sigaction old_sa;
	struct sigaction new_sa;

	sigemptyset(&new_sa.sa_mask);
	new_sa.sa_flags = 0;
	new_sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &new_sa, &old_sa);

	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (pipe(pipe_fds) < 0)
			{
				perror("pipe");
				sigaction(SIGINT, &old_sa, NULL);
				return (-1);
			}
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				close(pipe_fds[0]);
				close(pipe_fds[1]);
				sigaction(SIGINT, &old_sa, NULL);
				return (-1);
			}
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_IGN);
				close(pipe_fds[0]);
				read_heredoc_lines(pipe_fds[1], current, exec_ctx);
				close(pipe_fds[1]);
				exit(0);
			}
			close(pipe_fds[1]);
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			{
				close(pipe_fds[0]);
				write(1, "\n", 1);
				exec_ctx->last_exit = 130;
				sigaction(SIGINT, &old_sa, NULL);
				return (-1);
			}
			current->heredoc_pipe = pipe_fds[0];
		}
		current = current->next;
	}
	sigaction(SIGINT, &old_sa, NULL);
	return (0);
}

int	handle_heredoc(t_redir *redir)
{
	dup2(redir->heredoc_pipe, STDIN_FILENO);
	close(redir->heredoc_pipe);
	return (0);
}

int	apply_redirections(t_redir *redirections, t_exec *exec_ctx)
{
	t_redir	*current;
	int		result;

	(void)exec_ctx;
	current = redirections;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
			result = handle_input_redir(current->filename);
		else if (current->type == TOKEN_REDIR_OUT)
			result = handle_output_redir(current->filename);
		else if (current->type == TOKEN_APPEND)
			result = handle_append_redir(current->filename);
		else if (current->type == TOKEN_HEREDOC)
			result = handle_heredoc(current);
		else
			result = 0;
		if (result < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	pid_t	pid;
	int		status;
	int		saved_stdin;
	int		saved_stdout;
	char	*path;
	int		sig_num;

	if (!cmd)
		return (0);
	if (process_heredocs(cmd, exec_ctx) < 0)
	{
		exec_ctx->last_exit = 130;
		return (130);
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		if (saved_stdin != -1)
			close(saved_stdin);
		if (saved_stdout != -1)
			close(saved_stdout);
		exec_ctx->last_exit = 1;
		return (1);
	}
	if (apply_redirections(cmd->redirections, exec_ctx) < 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		exec_ctx->last_exit = 1;
		return (1);
	}
	if (!cmd->args || !cmd->args[0])
		status = 0;
	else if (is_builtin(cmd->args[0]))
		status = execute_builtin(cmd->args, exec_ctx);
	else
	{
		path = resolve_cmd_path(cmd->args[0], exec_ctx);
		if (!path)
		{
			error_msg("minishell", cmd->args[0], "command not found");
			status = 127;
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execve(path, cmd->args, exec_ctx->envp);

				if (errno == EACCES)
				{
					error_msg("minishell", cmd->args[0], "Permission denied");
					exit(126);
				}
				perror("minishell");
				exit(127);
			}
			else if (pid > 0)
			{
				free(path);
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
				waitpid(pid, &status, 0);
				signals();

				if (WIFEXITED(status))
					status = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
				{
					sig_num = WTERMSIG(status);
					if (sig_num == SIGQUIT)
						printf("Quit (core dumped)\n");
					else if (sig_num == SIGINT)
						printf("\n");
					status = 128 + sig_num;
				}
			}
			else
			{
				perror("fork");
				free(path);
				status = 1;
			}
		}
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	exec_ctx->last_exit = status;
	return (status);
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

void	setup_pipe_redirections(int **pipes, int cmd_index, int num_commands)
{
	if (cmd_index == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (cmd_index == num_commands - 1)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
}

void	execute_pipeline_command(t_cmd *cmd, t_exec *exec_ctx, int **pipes,
								int cmd_index, int num_commands)
{
	char	*path;
	int		status;

	if (pipes)
		setup_pipe_redirections(pipes, cmd_index, num_commands);
	if (apply_redirections(cmd->redirections, exec_ctx) < 0)
		exit(1);
	if (pipes)
		close_pipes(pipes, num_commands - 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd->args, exec_ctx);
		exit(status);
	}
	path = resolve_cmd_path(cmd->args[0], exec_ctx);
	if (!path)
	{
		error_msg("minishell", cmd->args[0], "command not found");
		exit(127);
	}
	execve(path, cmd->args, exec_ctx->envp);
	if (errno == EACCES)
	{
		error_msg("minishell", cmd->args[0], "Permission denied");
		exit(126);
	}
	else
	{
		perror("minishell");
		exit(127);
	}
}

int	execute_pipeline(t_cmd *commands, t_exec *exec_ctx)
{
	int		num_commands;
	int		**pipes;
	pid_t	*pids;
	int		i;
	int		status;
	int	sig_num;
	t_cmd	*current;

	if (!commands)
		return (1);
	num_commands = count_commands(commands);
	if (num_commands == 1)
		return (execute_simple_cmd(commands, exec_ctx));
	pipes = malloc(sizeof(int *) * (num_commands - 1));
	if (!pipes)
		return (1);
	pids = malloc(sizeof(pid_t) * num_commands);
	if (!pids)
	{
		free(pipes);
		return (1);
	}
	i = 0;
	while (i < num_commands - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	current = commands;
	while (current)
	{
		if (process_heredocs(current, exec_ctx) < 0)
		{
			exec_ctx->last_exit = 130;
			free(pids);
			return (130);
		}
		current = current->next;
	}
	current = commands;
	i = 0;
	while (i < num_commands && current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			execute_pipeline_command(current, exec_ctx, pipes, i, num_commands);
			exit(1);
		}
		current = current->next;
		i++;
	}
	close_pipes(pipes, num_commands - 1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	signals();
	if (WIFEXITED(status))
		exec_ctx->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig_num = WTERMSIG(status);
		if (sig_num == SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (sig_num == SIGINT)
			printf("\n");
		exec_ctx->last_exit = 128 + sig_num;
	}
	i = 0;
	while (i < num_commands - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(pids);
	return (exec_ctx->last_exit);
}

void	update_exit_status(t_exec *exec_ctx, int status)
{
	exec_ctx->last_exit = status;
}
