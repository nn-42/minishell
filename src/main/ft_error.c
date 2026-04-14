/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 23:40:39 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:53:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    error_msg(char *prefix, char *arg, char *msg)
{
    char    buf[1024];
    int     len;

    len = 0;
    if (prefix)
    {
        ft_memcpy(buf + len, prefix, ft_strlen(prefix));
        len += ft_strlen(prefix);
        ft_memcpy(buf + len, ": ", 2);
        len += 2;
    }
    if (arg)
    {
        ft_memcpy(buf + len, arg, ft_strlen(arg));
        len += ft_strlen(arg);
        ft_memcpy(buf + len, ": ", 2);
        len += 2;
    }
    if (msg)
    {
        ft_memcpy(buf + len, msg, ft_strlen(msg));
        len += ft_strlen(msg);
    }
    buf[len++] = '\n';
    write(STDERR_FILENO, buf, len); // ✅ atomic
}

/*void    error_msg(char *prefix, char *arg, char *msg)
{
    if (prefix)
    {
        ft_putstr_fd(prefix, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    if (arg)
    {
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    if (msg)
        ft_putstr_fd(msg, STDERR_FILENO);
    write(STDERR_FILENO, "\n", 1);
}*/

