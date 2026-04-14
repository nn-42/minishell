/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 18:18:22 by nfaronia          #+#    #+#             */
/*   Updated: 2026/04/14 12:43:00 by nfaronia         ###   ########.fr       */
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
		else if (str[i] == '\\' && in_double)
		{
			i++;
			if (str[i] == '"' || str[i] == '$' || str[i] == '\\')
				new_str = rest_char(new_str, str[i++]);
			else
			{
				new_str = rest_char(new_str, '\\');
				if (new_str)
					new_str = rest_char(new_str, str[i++]);
			}
		}
		else if (str[i] == '$' && !in_singel)
			new_str = expander_all_dollor(str, env, &i, new_str);
		else
			new_str = rest_char(new_str, str[i++]);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}

void remove_arg(char **args, int i)
{
    int j = i;

    free(args[i]);
    while (args[j + 1])
    {
        args[j] = args[j + 1];
        j++;
    }
    args[j] = NULL;
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	expander_args(char ***args, int *args_quoted, t_exec *env)
{
	int		i;
	char	*exp;
	char	**split;
	int		j;
	int		len;
	char	**new_args;
	int		num_words;

	i = 0;
	while (*args && (*args)[i])
	{
		exp = expander_all((*args)[i], env);
		if (!exp)
			return (expander_error("failed to expand argument"), 1);
		if (args_quoted[i] == NO_QUOTE)
		{
			split = ft_split(exp, ' ');
			free(exp);
			if (!split || !split[0])
			{
				free_split(split);
				remove_arg(*args, i);
				continue ;
			}
			// احسب عدد الكلمات
			num_words = 0;
			while (split[num_words])
				num_words++;
			// احسب طول args
			len = 0;
			while ((*args)[len])
				len++;
			new_args = malloc(sizeof(char *) * (len + num_words + 1));
			if (!new_args)
				return (free_split(split), 1);
			// قبل i
			j = 0;
			while (j < i)
			{
				new_args[j] = (*args)[j];
				j++;
			}
			// الكلمات الجديدة
			j = 0;
			while (j < num_words)
			{
				new_args[i + j] = ft_strdup(split[j]);
				j++;
			}
			// بعد i (تخطى العنصر القديم)
			j = i + 1;
			while ((*args)[j])
			{
				new_args[i + num_words + (j - i - 1)] = (*args)[j];
				j++;
			}
			new_args[len + num_words - 1] = NULL;
			free((*args)[i]);
			free(*args);
			*args = new_args;
			free_split(split);
			i += num_words; // ✅ تخطى الكلمات المُضافة كلها
		}
		else
		{
			free((*args)[i]);
			(*args)[i] = exp;
			i++;
		}
	}
	return (0);
}

int expander_redirs(t_redir *redir, t_exec *env)
{
    char    *exp;
    char    **split;

    while (redir)
    {
        // heredoc: وسّع فقط إذا NO_QUOTE، وبدون ambiguous check
        if (redir->type == TOKEN_REDIR_HEREDOC)
        {
            if (redir->quoted == NO_QUOTE)
            {
                exp = expander_all(redir->file, env);
                if (!exp)
                    return (1);
                free(redir->file);
                redir->file = exp;
            }
            redir = redir->next;
            continue ;
        }
        exp = expander_all(redir->file, env);
        if (!exp)
            return (1);
        if (redir->quoted == NO_QUOTE)
        {
            split = ft_split(exp, ' ');
            if (!split || !split[0] || split[1])
            {
                redir->ambiguous = 1;
                free(exp);
                free_split(split);
                redir = redir->next;
                continue ;
            }
            free_split(split);
        }
        free(redir->file);
        redir->file = exp;
        redir->ambiguous = 0;
        redir = redir->next;
    }
    return (0);
}
