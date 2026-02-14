/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:35:40 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/14 14:24:03 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;

	rl_catch_signals = 0;
	signals();
	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("minishell$ ");
		else
			line = readline(NULL);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		tokens = lexer(line);
		print_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
	rl_clear_history();
	return (0);
}
