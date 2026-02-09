/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:35:40 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/09 13:28:40 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (g_signal == SIGINT)
		{
			cntrc(&line);
			continue ;
		}
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
