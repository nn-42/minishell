/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:37:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/07 00:39:19 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "executor.h"
# include "minishell.h"

// expander.c
void	expander_error(char *msg);
char	*expander_all(char *str, t_exec *env);
int		expander_args(char **args, t_exec *env);
int		expander_redirs(t_redir *redir, t_exec *env);
int		expander(t_ast *node, t_exec *env);

// expander_quotes.c
void	single_quote(char **new_str, char *str, int *i);
void	double_quote(char **new_str, char *str, int *i);
char	*rest_char(char *new_str, char c);
char	*expander_quotes(char *str);

// expander_variables.c
char	*get_env_value(t_exec *env, char *var_name);
char	*var(char *str, int *i, t_exec *env);
char	*dollar_sign(char *str, t_exec *env, int *i, char *new_str);
char	*expander_variables(char *str, t_exec *env);

#endif