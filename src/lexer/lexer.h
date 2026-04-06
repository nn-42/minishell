/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:44:00 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/28 01:47:45 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// lexer.c
t_token	*lexer(char *line);
void	hori(char *line, int *i, t_token **tokens);
void	aort(char *line, int *i, t_token **tokens);
void	operator(char *line, int *i, t_token **tokens);
int		word(char *line, int *i, t_token **tokens);

// utils_lexer.c
void	lexer_error(char *msg);
void	is_null_lexer(char *value, t_token	*token);
int		add_token(t_token	**tokens, t_token_type type, char *value);
void	free_tokens(t_token *tokens);
int		quote(char **tokens_word, char *line, int *i);

// test_lexer.c
void	print_tokens(t_token *tokens);

#endif