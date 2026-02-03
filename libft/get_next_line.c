/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:01:09 by nfaronia          #+#    #+#             */
/*   Updated: 2026/01/11 12:41:50 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_file(int fd, char *buffer, char *stc)
{
	int		no_of_read;
	char	*free_str;

	if (!stc)
		stc = ft_strdup("");
	no_of_read = 1;
	while (no_of_read > 0 && !ft_strchr(stc, '\n'))
	{
		no_of_read = read(fd, buffer, BUFFER_SIZE);
		if (no_of_read < 0)
		{
			free(buffer);
			free(stc);
			return (NULL);
		}
		buffer[no_of_read] = '\0';
		free_str = stc;
		stc = ft_strjoin(stc, buffer);
		free (free_str);
		if (!stc)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stc);
}

static char	*line_pick(char *stc)
{
	size_t	i;

	i = 0;
	while (stc[i] != '\0' && stc[i] != '\n')
		i++;
	if (stc[i] == '\n')
		i++;
	return (ft_substr(stc, 0, i));
}

static char	*line_shift(char *stc)
{
	int		i;
	char	*new_line;

	i = 0;
	while (stc[i] && stc[i] != '\n')
		i++;
	if (!stc[i])
	{
		free(stc);
		return (NULL);
	}
	new_line = ft_substr(stc, i + 1, ft_strlen(stc) - i - 1);
	free(stc);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*stc[1024];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stc[fd] = read_file (fd, buffer, stc[fd]);
	if (!stc[fd] || *stc[fd] == '\0')
	{
		free(stc[fd]);
		stc[fd] = NULL;
		return (NULL);
	}
	line = line_pick(stc[fd]);
	stc[fd] = line_shift(stc[fd]);
	return (line);
}
