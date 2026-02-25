/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:30:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/25 16:42:57 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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

// signals.c
void	handler_cntrc(int sig);
void	handler_backslash(int sig);
void	signals(void);

// prompt.c
char	*read_input(void);
bool	is_empty_input(const char *input);

// history.c
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

// lexer.c
t_token	*lexer(char *line);
void	hori(char *line, int *i, t_token **tokens);
void	aort(char *line, int *i, t_token **tokens);
void	operator(char *line, int *i, t_token **tokens);
int		word(char *line, int *i, t_token **tokens);

// utils_lexer.c
void	is_null_lexer(char *value, t_token	*token);
int		add_token(t_token	**tokens, t_token_type type, char *value);
void	free_tokens(t_token *tokens);
int		quote(char **tokens_word, char *line, int *i);

// test_lexer.c
void	print_tokens(t_token *tokens);

// AST
typedef enum e_node_type
{
	NODE_CMD,
	NUDE_PIPE
}	t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	t_redir			*redirs;
}	t_ast;

typedef struct s_parser
{
	t_token	*current;
	int		error;
}	t_parser;

//parser.c
t_ast	*parse_pipe(t_parser *pars);
bool	pars_type(t_parser *pars);
t_ast	*parse_cmd(t_parser *pars);
t_ast	*parser(t_token *tokens);

//first_utis_parser.c
bool	is_match(t_parser *pars, t_token_type type);
void	adv(t_parser *pars);
t_ast	*creat_node(void);
t_ast	*pipe_node(t_ast *left, t_ast *right);
void	free_ast(t_ast *node);

//second_utils_parser.c
void	add_redir(t_ast *node, t_parser	*pars);
void	free_redir(t_redir *redir);
void	expand_args_array(char ***arr, char *str);
void	add_arg(t_ast *node, t_parser	*pars);
void	free_arg(char **arg);

//test_parser
void	print_ast(t_ast *node, int level, bool *levels);

#endif
