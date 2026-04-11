/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/11 06:59:54 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander_all_quotes(char c, int *in_singel, int *in_double)
{
	if (c == '\'' && !(*in_double))
	{
		*in_singel = !(*in_singel);
		return (1);
	}
	if (c == '"' && !(*in_singel))
	{
		*in_double = !(*in_double);
		return (1);
	}
	return (0);
}

char	*expander_all_dollor(char *str, t_exec *env, int *i, char *new_str)
{
	if (str[*i] == '$')
		return (dollar_sign(str, env, i, new_str));
	return (new_str);
}

char	*expander_all(char *str, t_exec *env)
{
	char	*new_str;
	int		i;
	int		in_singel;
	int		in_double;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	i = 0;
	in_double = 0;
	in_singel = 0;
	while (str[i])
	{
		if (expander_all_quotes(str[i], &in_singel, &in_double))
			i++;
		else if (str[i] == '$' && !in_singel)
			new_str = expander_all_dollor(str, env, &i, new_str);
		else
			new_str = rest_char(new_str, str[i++]);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}

int	expander_args(char **args, t_exec *env)
{
	int		i;
	char	*exp;

	i = 0;
	while (args && args[i])
	{
		exp = expander_all(args[i], env);
		if (!exp)
		{
			expander_error("failed to expand argument");
			while (args[i])
			{
				free(args[i]);
				args[i] = NULL;
				i++;
			}
			return (1);
		}
		free(args[i]);
		args[i] = exp;
		i++;
	}
	return (0);
}

int	expander_redirs(t_redir *redir, t_exec *env)
{
	char	*exp;

	while (redir)
	{
		exp = expander_all(redir->filename, env);
		if (!exp)
		{
			expander_error("failed to expand redir");
			while (redir)
			{
				free(redir->filename);
				redir->filename = NULL;
				redir = redir->next;
			}
			return (1);
		}
		free(redir->filename);
		redir->filename = exp;
		redir = redir->next;
	}
	return (0);
}
