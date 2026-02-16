/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:35:40 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/17 00:48:00 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmd_list;

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
		cmd_list = parse_tokens(tokens);
		if (cmd_list)
		{
			print_cmd(cmd_list);
			free_cmd(cmd_list);
		}
		//print_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
	rl_clear_history();
	return (0);
}
