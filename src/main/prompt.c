/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 08:49:05 by nnasered          #+#    #+#             */
/*   Updated: 2026/04/11 07:50:14 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_empty_input(const char *input)
{
	int	i;

	if (!input || !*input)
		return (true);
	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

char	*read_input(void)
{
	char	*input;

	if (isatty(STDIN_FILENO))
	{
		input = readline("minishell$ ");
	}
	else
	{
		printf("minishell$ ");
		fflush(stdout);
		input = readline("");
	}
	return (input);
}
