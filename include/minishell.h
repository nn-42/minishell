/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:30:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 00:47:30 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
//# define _POSIX_C_SOURCE 199309L
# define _POSIX_C_SOURCE 200809L

# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <signal.h>

extern int	g_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// signals
void	handler_cntrc(int sig);
void	handler_backslash(int sig);
void	signals(void);

// lexer
t_token	*lexer(char *line);
void	hori(char *line, int *i, t_token **tokens);
void	aort(char *line, int *i, t_token **tokens);
void	operator(char *line, int *i, t_token **tokens);
void	word(char *line, int *i, t_token **tokens);

// utils_lexer
int		add_token(t_token	**tokens, t_token_type type, char *value);
void	free_tokens(t_token *tokens);

//test_lexer
void	print_tokens(t_token *tokens);

#endif