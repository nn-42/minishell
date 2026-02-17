/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnasered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 08:48:58 by nnasered          #+#    #+#             */
/*   Updated: 2026/02/17 08:49:00 by nnasered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	rl_catch_signals = 0;
	init_history();
	signals();
	while (1)
	{
		input = read_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (is_empty_input(input))
		{
			free(input);
			continue ;
		}
		add_to_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	save_history();
	return (0);
}
