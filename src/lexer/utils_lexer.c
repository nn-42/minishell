/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:04:14 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 00:17:38 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(t_token	**tokens, t_token_type type, char *value)
{
	t_token	*token;
	t_token	*new_token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (0);
	}
	token->next = NULL;
	if (!*tokens)
		*tokens = token;
	else
	{
		new_token = *tokens;
		while (new_token->next)
			new_token = new_token->next;
		new_token->next = token;
	}
	return (1);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}
