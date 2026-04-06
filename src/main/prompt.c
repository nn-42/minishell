/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 08:49:05 by nnasered          #+#    #+#             */
/*   Updated: 2026/04/07 00:59:02 by nfaronia         ###   ########.fr       */
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
/*
static char	*get_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		return ("minishell$ ");
	}
	return ("");
}*/

char *read_input(void)
{
    char *input;

    if (isatty(STDIN_FILENO))
    {
        input = readline("minishell$ ");
    }
    else
    {
        input = get_next_line(STDIN_FILENO); // أو getline
        if (input)
        {
            // حذف newline إذا موجود
            int len = strlen(input);
            if (len > 0 && input[len - 1] == '\n')
                input[len - 1] = '\0';
        }
    }
    return input;
}

/*
char	*read_input(void)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt();
	input = readline(prompt);
	return (input);
}*/
