/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnasered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:38:00 by nnasered          #+#    #+#             */
/*   Updated: 2025/10/23 12:02:29 by nnasered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define MAX_SAFE_BUFFER 65536

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE > MAX_SAFE_BUFFER
#   undef BUFFER_SIZE
#   define BUFFER_SIZE MAX_SAFE_BUFFER
#  endif
# else
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
size_t	ft_gnl_strlen(const char *s);
char	*ft_gnl_strchr(const char *s, int c);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_strdup(const char *s);
void	copy_line_content(char *dest, const char **src, size_t len);
#endif
