#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include "get_next_line.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell$ "
#define HISTORY_FILE ".minishell_history"
#define MAX_HISTORY 1000

extern volatile sig_atomic_t g_signal;


typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
} t_token_type;

typedef struct s_token
{
	t_token_type type;
	char *value;
	struct s_token *next;
} t_token;

typedef struct s_redir
{
	t_token_type type;
	char *file;
	struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
	char **args;
	t_redir *redirections;
	struct s_cmd *next;
} t_cmd;

typedef struct s_exec
{
	char **envp;
	int last_exit;
} t_exec;

/* prompt.c */
char	*read_input(void);
bool	is_empty_input(const char *input);

/* history.c */
void	init_history(void);
void	add_to_history(const char *input);
void	save_history(void);

/* signals.c */
void	setup_signals(void);

/* lexer.c */
t_token	*tokenize(char *input);
void	free_tokens(t_token *tokens);

/* lexer_utils.c */
t_token *create_token(t_token_type type, char *value);
void    add_token(t_token **tokens, t_token *new);

/* parser.c */
t_cmd   *parse(t_token *tokens);
void    free_commands(t_cmd *commands);

/* executor.c */
int	execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx);
int	execute_pipeline(t_cmd *commands, t_exec *exec_ctx);
void	update_exit_status(t_exec *exec_ctx, int status);
char	*resolve_cmd_path(char *command, t_exec *exec_ctx);
int	apply_redirections(t_redir *redirections, t_exec *exec_ctx);

/* expander.c */
void	expand_commands(t_cmd *commands, t_exec *exec_ctx);
char	*expand_variables(char *str, t_exec *exec_ctx);

/* builtins.c */
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_exec *exec_ctx);
void	cleanup_shell(void);
int     builtin_exit(char **args, t_exec *exec_ctx);
int	builtin_env(char **args, t_exec *exec_ctx);
int		builtin_echo(char **args);
int		builtin_unset(char **args, t_exec *exec_ctx);
int		builtin_pwd(void);
int		builtin_cd(char **args, t_exec *exec_ctx);

/* env.c */
char	**dup_env(char **envp);
void	free_env(char **envp);
int		set_env_var(char ***envp, char *name, char *value);
int		find_env_var(char **envp, char *name);
int		builtin_export(char **args, t_exec *exec_ctx);
int     count_env_vars(char **envp);

#endif
