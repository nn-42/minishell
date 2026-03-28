#include "minishell.h"

void	print_export_format(char **envp)
{
	int		i;
	char	*equals;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i])
	{
		equals = ft_strchr(envp[i], '=');

		if (equals)
		{
			name = ft_substr(envp[i], 0, equals - envp[i]);
			value = equals + 1;
			printf("declare -x %s=\"%s\"\n", name, value);
			free(name);
		}
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**dup_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = count_env_vars(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;

	return (new_env);
}

void	free_env(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

///////////////update_existing_var///////////////////
int	find_env_var(char **envp, char *name)
{
	int		i;
	int		name_len;

	if (!envp || !name)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	update_env_var(char ***envp, char *name, char *value)
{
	int		index;
	char	*new_var;
	char	*temp;

	index = find_env_var(*envp, name);
	if (index == -1)
		return (0);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (-1);
	new_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_var)
		return (-1);
	free((*envp)[index]);
	(*envp)[index] = new_var;
	return (1);
}
/////////////////////////////////

///////////add_new_var/////////////
int	add_env_var(char ***envp, char *name, char *value)
{
	char	**new_env;
	char	*new_var;
	char	*temp;
	int		count;
	int		i;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (-1);
	new_var = ft_strjoin(temp, value);
	free(temp);	
	if (!new_var)
		return (-1);
	count = count_env_vars(*envp);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_var);
		return (-1);
	}
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free(*envp);
	*envp = new_env;
	
	return (1);
}
///////////////////////

//////////////////final_set_and_update//////////////////
int	set_env_var(char ***envp, char *name, char *value)
{
	int	result;

	result = update_env_var(envp, name, value);
	
	if (result == 1)
		return (0);	
	if (result == -1)
		return (-1);
	result = add_env_var(envp, name, value);
	if (result == -1)
		return (-1);
	return (0);
}
/////////////////////////////////////

////////////final_export_builtin///////////
int	parse_export_arg(char *arg, char **name, char **value)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	
	// No '=' means just declaration (we'll skip this for now)???
	if (!equals)
		return (0);
	*name = ft_substr(arg, 0, equals - arg);
	*value = ft_strdup(equals + 1);
	if (!*name || !*value)
	{
		free(*name);
		free(*value);
		return (0);
	}
	return (1);
}

int	builtin_export(char **args, t_exec *exec_ctx)
{
	int		i;
	char	*name;
	char	*value;

	// No arguments: print all in export format
	if (!args[1])
	{
		print_export_format(exec_ctx->envp);
		return (0);
	}

	// Process each argument
	i = 1;
	while (args[i])
	{
		if (parse_export_arg(args[i], &name, &value))
		{
			// Has '=' - set the variable
			if (set_env_var(&exec_ctx->envp, name, value) < 0)
			{
				printf("export: failed to set %s\n", name);
				free(name);
				free(value);
				return (1);
			}
			free(name);
			free(value);
		}
		else
		{
			// No '=' - just declaration (export VAR)
			printf("export: `%s': not a valid identifier\n", args[i]);
		}
		i++;
	}

	return (0);
}
///////////////////////////////
