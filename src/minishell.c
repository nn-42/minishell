/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:35:40 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 01:03:57 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;

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
		//lexer(line);
		tokens = lexer(line);
		print_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
	rl_clear_history();
	return (0);
}
