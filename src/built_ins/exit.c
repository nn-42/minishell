/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 05:53:40 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:20:29 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
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

static void	get_limit_and_start(const char *str, const char **limit, int *start)
{
	*start = 0;
	if (str[0] == '+' || str[0] == '-')
		*start = 1;
	if (str[0] == '-')
		*limit = LL_MIN;
	else
		*limit = LL_MAX;
}

static int	is_out_of_range(char *str)
{
	const char	*limit;
	int			start;
	int			len;
	int			i;

	get_limit_and_start(str, &limit, &start);
	len = ft_strlen(str + start);
	if (len > (int)ft_strlen(limit))
		return (1);
	if (len < (int)ft_strlen(limit))
		return (0);
	i = 0;
	while (limit[i])
	{
		if (str[start + i] > limit[i])
			return (1);
		if (str[start + i] < limit[i])
			return (0);
		i++;
	}
	return (0);
}

int	builtin_exit(char **args, t_exec *exec_ctx)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1])
	{
		exit_code = exec_ctx->last_exit;
		cleanup_shell(exec_ctx);
		exit(exit_code);
	}
	if (!is_num(args[1]) || is_out_of_range(args[1]))
	{
		error_msg("exit", args[1], "numeric argument required");
		cleanup_shell(exec_ctx);
		exit(2);
	}
	if (args[2])
	{
		error_msg("minishell", "exit", "too many arguments");
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	cleanup_shell(exec_ctx);
	exit(exit_code);
}
