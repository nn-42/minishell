/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:52:49 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:56:58 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

// main.c
int		init_exec(t_exec *exec_ctx, char **envp);
int		handle_input(char **input);
void	process_line(char *input, t_exec *exec_ctx);

// prompt.c
char	*read_input(void);
bool	is_empty_input(const char *input);

/* history.c */
void	init_history(void);
void	add_to_history(const char *input);
void	save_history(void);
void    free_history(void);

// history_utils.c
void	load_history(void);

// ft_error.c
void    error_msg(char *prefix, char *arg, char *msg);

#endif