/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnasered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:37:41 by nnasered          #+#    #+#             */
/*   Updated: 2025/10/26 11:18:17 by nnasered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	calculate_len(char *eol_ptr, char **stash)
{
	if (eol_ptr != NULL)
		return (eol_ptr - *stash + 1);
	else
		return (ft_gnl_strlen(*stash));
}

static char	*extract_line(char **stash)
{
	char	*eol_ptr;
	char	*line;
	char	*rest;
	size_t	len;

	if (!*stash || !**stash)
		return (NULL);
	eol_ptr = ft_gnl_strchr(*stash, '\n');
	len = calculate_len(eol_ptr, stash);
	line = malloc(len + 1);
	if (!line)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	copy_line_content(line, (const char **)stash, len);
	if (eol_ptr != NULL)
		rest = ft_gnl_strdup(eol_ptr + 1);
	else
		rest = NULL;
	free(*stash);
	*stash = rest;
	return (line);
}

static int	read_to_stash(int fd, char **stash)
{
	char	*buffer;
	char	*temp;
	ssize_t	read_count;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	read_count = read(fd, buffer, BUFFER_SIZE);
	if (read_count <= 0)
	{
		free(buffer);
		return (read_count);
	}
	buffer[read_count] = '\0';
	temp = ft_gnl_strjoin(*stash, buffer);
	free(buffer);
	if (!temp)
		return (-1);
	free(*stash);
	*stash = temp;
	return (read_count);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	ssize_t		read_count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_count = 1;
	while (read_count > 0)
	{
		if (stash && ft_gnl_strchr(stash, '\n'))
			break ;
		read_count = read_to_stash(fd, &stash);
		if (read_count < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
	}
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (extract_line(&stash));
}

/*
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static ssize_t	buf_len = 0;
	static ssize_t	buf_pos = 0;
	char			*line;
	char			*new_line;
	ssize_t			line_cap;
	ssize_t			line_len;
	ssize_t			i;
	ssize_t			j;
	ssize_t			k;
	ssize_t			new_size;

	line = NULL;
	new_line = NULL;
	line_cap = 0;
	line_len = 0;
	i = 0;
	j = 0;
	k = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buf_pos >= buf_len)
		{
			buf_len = read(fd, buf, BUFFER_SIZE);
			buf_pos = 0;
			if (buf_len < 0)
			{
				if (line != NULL)
					free(line);
				return (NULL);
			}
			if (buf_len == 0)
				break ;
		}
		i = buf_pos;
		while (i < buf_len && buf[i] != '\n')
			i++;
		j = i - buf_pos;
		if (i < buf_len && buf[i] == '\n')
			j = j + 1;
		if (j == 0 && buf_len == 0)
			break ;
		if (line_len + j + 1 > line_cap)
		{
			if (line_cap == 0)
				new_size = j + 1;
			else
				new_size = line_cap * 2;
			if (new_size < line_len + j + 1)
				new_size = line_len + j + 1;
			new_line = malloc(new_size);
			if (new_line == NULL)
			{
				if (line != NULL)
					free(line);
				return (NULL);
			}
			if (line != NULL)
			{
				k = 0;
				while (k < line_len)
				{
					new_line[k] = line[k];
					k++;
				}
				free(line);
			}
			line = new_line;
			line_cap = new_size;
		}
		k = 0;
		while (k < j && buf_pos < buf_len)
		{
			line[line_len] = buf[buf_pos];
			line_len++;
			buf_pos++;
			k++;
		}
		if (line_len > 0)
			line[line_len] = '\0';
		if (buf_pos > 0 && buf[buf_pos - 1] == '\n')
			break ;
		if (buf_len < BUFFER_SIZE && buf_pos >= buf_len)
			break ;
	}
	if (line != NULL && line_len > 0)
		return (line);
	if (line != NULL)
		free(line);
	return (NULL);
}
 */
