/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:30:29 by nfaronia          #+#    #+#             */
/*   Updated: 2026/03/31 14:15:05 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _POSIX_C_SOURCE 200809L

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
# include <errno.h>

// Project headers
# include "libft.h"
# include "get_next_line.h"
# include "signals.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "expander.h"
# include "built_ins.h"
# include "main.h"

# define PROMPT "minishell$ "
# define HISTORY_FILE ".minishell_history"
# define MAX_HISTORY 1000

#endif
