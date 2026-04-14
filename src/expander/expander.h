/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:37:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:55:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "executor.h"
# include "minishell.h"

// expander.c
void	expander_error(char *msg);
int		expander(t_ast *node, t_exec *env);

// expander_quotes.c
void	single_quote(char **new_str, char *str, int *i);
void	double_quote(char **new_str, char *str, int *i);
char	*rest_char(char *new_str, char c);
char	*expander_quotes(char *str);

// expander_variables.c
char	*get_env_value(t_exec *env, char *var_name);
char	*var_nname(char *str, int *i);
char	*var(char *str, int *i, t_exec *env);
char	*dollar_sign(char *str, t_exec *env, int *i, char *new_str);
char	*expander_variables(char *str, t_exec *env);

// expander_all.c
int		expander_all_quotes(char c, int *in_singel, int *in_double);
char	*expander_all_dollor(char *str, t_exec *env, int *i, char *new_str);
char	*expander_all(char *str, t_exec *env);
int     expander_args(char ***args, int *args_quoted, t_exec *env);
int		expander_redirs(t_redir *redir, t_exec *env);

#endif