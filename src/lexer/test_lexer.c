/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:02:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 00:50:07 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	const char		*name;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			name = "TOKEN_WORD";
		else if (tokens->type == TOKEN_PIPE)
			name = "TOKEN_PIPE";
		else if (tokens->type == TOKEN_REDIR_IN)
			name = "TOKEN_REDIR_IN";
		else if (tokens->type == TOKEN_REDIR_OUT)
			name = "TOKEN_REDIR_OUT";
		else if (tokens->type == TOKEN_APPEND)
			name = "TOKEN_APPEND";
		else if (tokens->type == TOKEN_HEREDOC)
			name = "TOKEN_HEREDOC";
		else
			name = "UNKNOWN";
			
		printf("[%s:%s] ", name, tokens->value);
		tokens = tokens->next;
	}
	printf("\n");
}
