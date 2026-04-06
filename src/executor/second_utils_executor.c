/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils_executor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:03:35 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 14:28:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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

void	read_loop(char *delimiter, int fd, t_exec *exec_ctx)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expander_variables(line, exec_ctx);
		free(line);
		if (!expanded)
			continue ;
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
}

int	handle_heredoc(char *delimiter, t_exec *exec_ctx)
{
	int		pipe_fds[2];

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		return (-1);
	}
	read_loop(delimiter, pipe_fds[1], exec_ctx);
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
			result = handle_input_redir(current->filename);
		else if (current->type == TOKEN_REDIR_OUT)
			result = handle_output_redir(current->filename);
		else if (current->type == TOKEN_APPEND)
			result = handle_append_redir(current->filename);
		else if (current->type == TOKEN_HEREDOC)
			result = handle_heredoc(current->filename, exec_ctx);
		else
			result = 0;
		if (result < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
