/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 07:22:45 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/11 00:41:51 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dash_n(char *n)
{
	int	i;

	if (!n || n[0] != '-')
		return (0);
	i = 1;
	while (n[i])
	{
		if (n[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	built_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (args[i] && dash_n(args[i]))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
