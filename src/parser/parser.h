/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:46:08 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/07 07:13:36 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "executor.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE
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

// parser.c
void	parse_error(char *msg);
void	free_ast(t_ast *node);
t_ast	*parser(t_token *tokens);

// parse_pipe.c
t_ast	*pipe_node(t_ast *left, t_ast *right);
bool	match_token(t_parser *pars, t_token_type type);
t_ast	*parse_pipe(t_parser *pars);

// parse_cmd.c
t_ast	*cmd_node(void);
bool	pars_type(t_parser *pars);
void	next_token(t_parser *pars);
t_ast	*parse_cmd(t_parser *pars);

//utils_cmd.c
void	add_redir(t_ast *node, t_parser	*pars);
void	free_redir(t_redir *redir);
void	expand_args_array(char ***arr, char *str);
void	add_arg(t_ast *node, t_parser	*pars);
void	free_arg(char **arg);

// translation_function.c
t_cmd	*create_cmd_from_ast(t_ast *node);
t_cmd	*ast_to_cmd_list(t_ast *node);
void	free_cmd_list(t_cmd *cmd);

#endif