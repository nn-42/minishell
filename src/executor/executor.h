/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 02:03:16 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:22:13 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include "minishell.h"

typedef struct s_redir	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char	**envp;
	int		last_exit;
}	t_exec;

/* executor.c */
int	execute_simple_cmd(t_cmd *cmd, t_exec *exec_ctx);
int	execute_pipeline(t_cmd *commands, t_exec *exec_ctx);
void	update_exit_status(t_exec *exec_ctx, int status);
char	*resolve_cmd_path(char *command, t_exec *exec_ctx);
int	apply_redirections(t_redir *redirections, t_exec *exec_ctx);
int	process_heredocs(t_cmd *cmd, t_exec *exec_ctx);

#endif