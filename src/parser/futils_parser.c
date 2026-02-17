/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futils_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:57:47 by nfaronia          #+#    #+#             */
/*   Updated: 2026/02/16 23:49:55 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_null_parser(char *file, t_redir *redir)
{
	if (file)
		redir->file = ft_strdup(file);
	else
		redir->file = NULL;
}

t_redir	*add_redirections(t_redir *redirections, t_token_type type, char *file)
{
	t_redir	*redir;
	t_redir	*current;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	is_null_parser(file, redir);
	if (file && !redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	if (!redirections)
		return (redir);
	current = redirections;
	while (current->next)
		current = current->next;
	current->next = redir;
	return (redirections);
}

int	copy_args(char **new_args, char **args, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		new_args[j] = args[j];
		j++;
	}
	return (j);
}

char	**add_args(char **args, char *word)
{
	int		i;
	char	**new_args;

	i = 0;
	while (args && args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	copy_args(new_args, args, i);
	new_args[i] = ft_strdup(word);
	if (!new_args[i])
	{
		free(new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}
