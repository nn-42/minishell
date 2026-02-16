/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:58:17 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/17 00:49:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_token	*handle_word(t_cmd	*cmd_curr, t_token	*tok)
{
	cmd_curr->args = add_args(cmd_curr->args, tok->value);
	return (tok->next);
}

t_token	*handle_redirection(t_cmd	*cmd_curr, t_token	*tok)
{
	t_token_type	r_type;

	r_type = tok->type;
	tok = tok->next;
	if (!tok || tok->type != TOKEN_WORD)
	{
		printf("syntax error: redirection without file\n");
		return (NULL);
	}
	cmd_curr->redirections = add_redirections(cmd_curr->redirections,
			r_type, tok->value);
	return (tok->next);
}

t_token	*handle_pipe(t_cmd **cmd_curr, t_token *tok)
{
	t_cmd	*new;

	if (!(*cmd_curr)->args)
	{
		printf("syntax error: empty command before pipe\n");
		return (NULL);
	}
	new = new_cmd();
	if (!new)
		return (NULL);
	(*cmd_curr)->next = new;
	*cmd_curr = new;
	return (tok->next);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd_curr;
	t_token	*tok;

	cmd_head = NULL;
	cmd_curr = NULL;
	tok = tokens;
	while (tok && tok->type != TOKEN_EOF)
	{
		if (!cmd_curr)
		{
			cmd_curr = new_cmd();
			if (!cmd_curr)
				return (NULL);
			cmd_head = cmd_curr;
		}
		if (tok->type == TOKEN_WORD)
			tok = handle_word(cmd_curr, tok);
		else if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_REDIR_OUT
			|| tok->type == TOKEN_APPEND || tok->type == TOKEN_HEREDOC)
			tok = handle_redirection(cmd_curr, tok);
		else if (tok->type == TOKEN_PIPE)
			tok = handle_pipe(&cmd_curr, tok);
		else
			tok = tok->next;
		if (!tok)
			return (NULL);
	}
	if (cmd_curr && !cmd_curr->args)
	{
		printf("syntax error: empty command\n");
		return (NULL);
	}
	return (cmd_head);
}
