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
		if (is_executable(command))
			return (ft_strdup(command));
		return (NULL);
	}
	return (find_command_in_path(command, exec_ctx));
}

////////////////////redirection//////////////////////
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

int	handle_heredoc(char *delimiter, t_exec *exec_ctx)
{
	int		pipe_fds[2];
	char	*line;
	char	*expanded;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_variables(line, exec_ctx);
		free(line);
		write(pipe_fds[1], expanded, ft_strlen(expanded));
		write(pipe_fds[1], "\n", 1);
		free(expanded);
	}

	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);

	return (0);
}

int	apply_redirections(t_redir *redirections, t_exec *exec_ctx)
{
	t_redir	*current;
	int		result;

	current = redirections;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
			result = handle_input_redir(current->file);
		else if (current->type == TOKEN_REDIR_OUT)
			result = handle_output_redir(current->file);
		else if (current->type == TOKEN_REDIR_APPEND)
			result = handle_append_redir(current->file);
		else if (current->type == TOKEN_REDIR_HEREDOC)
			result = handle_heredoc(current->file, exec_ctx);
		else
			result = 0;

		if (result < 0)
			return (-1);

		current = current->next;
	}

	return (0);
}
///////////////////////////////

int	execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
	{
		int saved_stdin;
		int saved_stdout;
		
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
	path = resolve_cmd_path(cmd->args[0], exec_ctx);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		exec_ctx->last_exit = 127;
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		if (apply_redirections(cmd->redirections, exec_ctx) < 0)
			exit(1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->args, exec_ctx->envp);
		perror("minishell");
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
	else
	{
		perror("fork");
		free(path);
		return (1);
	}
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

void	execute_pipeline_command(t_cmd *cmd, t_exec *exec_ctx, int **pipes,
								int cmd_index, int num_commands)
{
	char	*path;
	int	status;

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
		printf("minishell: %s: command not found\n", cmd->args[0]);
		exit(127);
	}

	execve(path, cmd->args, exec_ctx->envp);
	perror("minishell");
	exit(127);
}

int	execute_pipeline(t_cmd *commands, t_exec *exec_ctx)
{
	int		num_commands;
	int		**pipes;
	pid_t	*pids;
	int		i;
	int		status;
	t_cmd	*current;

	num_commands = count_commands(commands);
	if (num_commands == 1)
		return (execute_simple_cmd(commands, exec_ctx));
	pipes = malloc(sizeof(int *) * (num_commands - 1));
	pids = malloc(sizeof(pid_t) * num_commands);
	i = 0;
	while (i < num_commands - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	current = commands;
	i = 0;
	while (i < num_commands)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			execute_pipeline_command(current, exec_ctx, pipes, i, num_commands);
		}
		current = current->next;
		i++;
	}
	close_pipes(pipes, num_commands - 1);
	i = 0;
	while (i < num_commands)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exec_ctx->last_exit = WEXITSTATUS(status);
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
