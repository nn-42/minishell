/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:53:40 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 05:54:50 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_exec *exec_ctx)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
	{
		exit_code = exec_ctx->last_exit;
		cleanup_shell();
		exit(exit_code);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (!is_num(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		cleanup_shell();
		exit(2);
	}
	exit_code = ft_atoi(args[1]);
	cleanup_shell();
	exit(exit_code);
}
