#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	quote = 0;
	
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
		{
			quote = str[i];
			i++;
			continue;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
			continue;
		}
		result[j++] = str[i++];
	}
	
	result[j] = '\0';
	return (result);
}

void	expand_command_args(t_cmd *cmd)
{
	int		i;
	char	*expanded;

	if (!cmd || !cmd->args)
		return;

	i = 0;
	while (cmd->args[i])
	{
		expanded = remove_quotes(cmd->args[i]);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

void	expand_redirections(t_redir *redirections)
{
	t_redir	*current;
	char	*expanded;

	current = redirections;
	while (current)
	{
		expanded = remove_quotes(current->file);
		if (expanded)
		{
			free(current->file);
			current->file = expanded;
		}
		current = current->next;
	}
}

/////////////////////var//////
int	get_var_name_len(char *str)
{
	int	len;

	len = 0;
	if (str[0] == '?')
		return (1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	
	return (len);
}

char	*get_var_value(char *var_name, int len, t_exec *exec_ctx)
{
	char	*name;
	char	*value;
	int		index;

	if (len == 1 && var_name[0] == '?')
		return (ft_itoa(exec_ctx->last_exit));
	name = ft_substr(var_name, 0, len);
	if (!name)
		return (ft_strdup(""));
	index = find_env_var(exec_ctx->envp, name);
	free(name);
	if (index == -1)
		return (ft_strdup(""));
	value = ft_strchr(exec_ctx->envp[index], '=');
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value + 1));
}

char    *append_char(char *str, char c)
{
        char    *new_str;
        int             len;

        len = ft_strlen(str);
        new_str = malloc(len + 2);
        if (!new_str)
        {
                free(str);
                return (NULL);
        }
        ft_memcpy(new_str, str, len);
        new_str[len] = c;
        new_str[len + 1] = '\0';
        free(str);
        return (new_str);
}

char    *str_append_str(char **s1, char *s2)
{
        char    *result;

        result = ft_strjoin(*s1, s2);
        free(*s1);
        *s1 = result;
        return (result);
}

char	*expand_variables(char *str, t_exec *exec_ctx)
{
	char	*result;
	char	*var_value;
	int		i;
	int		var_len;
	char	quote;

	if (!str)
		return (NULL);
	
	result = ft_strdup("");
	i = 0;
	quote = 0;
	
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		if (str[i] == '$' && quote != '\'')
		{
			var_len = get_var_name_len(str + i + 1);	
			if (var_len > 0)
			{
				var_value = get_var_value(str + i + 1, var_len, exec_ctx);
				result = str_append_str(&result, var_value);
				free(var_value);
				i += var_len + 1;
				continue;
			}
		}
		result = append_char(result, str[i]);
		i++;
	}
	return (result);
}

void	expand_variables_in_args(t_cmd *cmd, t_exec *exec_ctx)
{
	int		i;
	char	*expanded;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_variables(cmd->args[i], exec_ctx);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

void	expand_variables_in_redirections(t_redir *redirections, t_exec *exec_ctx)
{
	t_redir	*current;
	char	*expanded;

	current = redirections;
	while (current)
	{
		expanded = expand_variables(current->file, exec_ctx);
		if (expanded)
		{
			free(current->file);
			current->file = expanded;
		}
		current = current->next;
	}
}
////////////////////////////

void	expand_commands(t_cmd *commands, t_exec *exec_ctx)
{
	t_cmd	*current;

	current = commands;
	while (current)
	{
		expand_variables_in_args(current, exec_ctx);
		expand_variables_in_redirections(current->redirections, exec_ctx);
		expand_command_args(current);
		expand_redirections(current->redirections);	
		current = current->next;
	}
}
