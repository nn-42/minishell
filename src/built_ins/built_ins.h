/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:29:33 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 05:56:15 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

// builtins.c
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_exec *exec_ctx);
void	cleanup_shell(void);

// cd.c
char	*get_home(t_exec *exec_ctx, char *old_pwd);
char	*get_path(char **args, t_exec *exec_ctx, char *old_pwd);
int		set_env(char *old_pwd, t_exec *exec_ctx);
int		builtin_cd(char **args, t_exec *exec_ctx);

// echo.c
int		built_echo(char **args);

// env.c
int		builtin_env(char **args, t_exec *exec_ctx);

// pwd.c
int		built_pwd(void);

// export.c
int		update_env_var(char ***envp, char *name, char *value);
int		set_env_var(char ***envp, char *name, char *value);
int		parse_export_arg(char *arg, char **name, char **value);
int		export_arg(char *arg, t_exec *exec_ctx);
int		builtin_export(char **args, t_exec *exec_ctx);

// first_utils_export.c
void	print_export_format(char **envp);
int		count_env_vars(char **envp);
char	**dup_env(char **envp);
void	free_env(char **envp);
int		find_env_var(char **envp, char *name);

// second_utils_export.c
char	*build_var(char *name, char *value);
int		add_env_var(char ***envp, char *name, char *value);

// unset.c
void	copy_env(char ***envp, char **new_env, int index, int count);
int		unset_env_var(char ***envp, char *name);
int		builtin_unset(char **args, t_exec *exec_ctx);

// exit.c
int		is_num(char *str);
int		builtin_exit(char **args, t_exec *exec_ctx);

#endif