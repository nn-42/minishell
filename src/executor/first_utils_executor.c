/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_utils_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:03:35 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/07 07:11:48 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	is_executable(char *path)
{
	if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*search_in_path(char **paths, char *command)
{
	char	*full_path;
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (is_executable(full_path))
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_in_path(char *command, t_exec *exec_ctx)
{
	char	*path_env;
	char	**paths;
	char	*result;
	int		index;
	int		i;

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
	result = search_in_path(paths, command);
	if (result)
		return (result);
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
