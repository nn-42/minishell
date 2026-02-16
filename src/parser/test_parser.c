/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:05:49 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/17 00:45:43 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*r;

	while (cmd)
	{
		printf("Command:\n");
		if (cmd->args)
		{
			printf("  args: ");
			i = 0;
			while (cmd->args[i])
			{
				printf("[%s] ", cmd->args[i]);
				i++;
			}
			printf("\n");
		}
		r = cmd->redirections;
		while (r)
		{
			printf("  redir: %d -> %s\n", r->type, r->file);
			r = r->next;
		}
		cmd = cmd->next;
	}
}
