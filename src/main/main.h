/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 01:52:49 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/28 01:54:00 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

// prompt.c
char	*read_input(void);
bool	is_empty_input(const char *input);

// history.c
void	init_history(void);
void	add_to_history(const char *input);
void	save_history(void);

#endif