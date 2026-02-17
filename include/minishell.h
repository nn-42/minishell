/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:30:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/17 00:46:07 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
//# define _POSIX_C_SOURCE 199309L
# define _POSIX_C_SOURCE 200809L

# include "libft.h"
# include "get_next_line.h"
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

# define PROMPT "minishell$ "
# define HISTORY_FILE ".minishell_history"
# define MAX_HISTORY 1000

extern int	g_signal;

// signals
void	handler_cntrc(int sig);
void	handler_backslash(int sig);
void	signals(void);

/* prompt.c */
char	*read_input(void);
bool	is_empty_input(const char *input);

/* history.c */
void	init_history(void);
void	add_to_history(const char *input);
void	save_history(void);

// lexer
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

// lexer
t_token	*lexer(char *line);
void	hori(char *line, int *i, t_token **tokens);
void	aort(char *line, int *i, t_token **tokens);
void	operator(char *line, int *i, t_token **tokens);
int		word(char *line, int *i, t_token **tokens);

// utils_lexer
void	is_null_lexer(char *value, t_token	*token);
int		add_token(t_token	**tokens, t_token_type type, char *value);
void	free_tokens(t_token *tokens);
int		quote(char **tokens_word, char *line, int *i);

//test_lexer
void	print_tokens(t_token *tokens);

// parser

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

//parser


//first_util_parser
void	is_null_parser(char *file, t_redir *redir);
t_redir	*add_redirections(t_redir *redirections, t_token_type type, char *file);
int		copy_args(char **new_args, char **args, int i);
char	**add_args(char **args, char *word);

//second_utils_parser
void	free_redirections(t_redir *redir);
void	free_args(char **args);
void	free_cmd(t_cmd *cmd);

//parser
t_cmd	*new_cmd(void);
t_token	*handle_word(t_cmd	*cmd_curr, t_token	*tok);
t_token	*handle_redirection(t_cmd	*cmd_curr, t_token	*tok);
t_token	*handle_pipe(t_cmd **cmd_curr, t_token *tok);
t_cmd	*parse_tokens(t_token *tokens);

//test_parser
void	print_cmd(t_cmd *cmd);

#endif
