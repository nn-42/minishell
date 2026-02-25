/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutils_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:43:04 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/25 15:40:12 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir(t_ast *node, t_parser	*pars)
{
	t_redir			*redir;
	t_token_type	type;

	type = pars->current->type;
	adv(pars);
	if (!pars->current || pars->current->type != TOKEN_WORD)
	{
		printf("syntax error near redirection\n");
		pars->error = 1;
		return ;
	}
	redir = malloc(sizeof(t_redir));
	if (!redir)
	{
		pars->error = 1;
		return ;
	}
	redir->type = type;
	redir->filename = ft_strdup(pars->current->value);
	redir->next = node->redirs;
	node->redirs = redir;
	adv(pars);
}

void	free_redir(t_redir *redir)
{
	t_redir	*f;

	while (redir)
	{
		f = redir;
		redir = redir->next;
		if (f->filename)
			free(f->filename);
		free(f);
	}
}

void	expand_args_array(char ***arr, char *str)
{
	int		len;
	char	**new_arr;
	int		i;

	len = 0;
	while (*arr && (*arr)[len])
		len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return ;
	i = 0;
	while (i < len)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	new_arr[len] = str;
	new_arr[len + 1] = NULL;
	free(*arr);
	*arr = new_arr;
}

void	add_arg(t_ast *node, t_parser	*pars)
{
	char	*s;

	s = ft_strdup(pars->current->value);
	if (!s)
	{
		pars->error = 1;
		return ;
	}
	expand_args_array(&node->args, s);
	adv(pars);
}

void	free_arg(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
