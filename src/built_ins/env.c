/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 04:58:40 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:00:24 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **args, t_exec *exec_ctx)
{
	int	i;

	if (args[1])
	{
		error_msg("env", args[1], "No such file or directory");
		return (127);
	}
	i = 0;
	while (exec_ctx->envp[i])
	{
		printf("%s\n", exec_ctx->envp[i]);
		i++;
	}
	return (0);
}
